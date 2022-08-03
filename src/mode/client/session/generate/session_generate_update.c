/*
 * Rodzhang
 *
 */

#include "session_generate_update.h"
#include <spate_net.h>
#include <spate_tick.h>
#include <spate_fack_tcp.h>
#include <spate_utils.h>


static inline void __engress_tcp_syn_reset_tick_id(session_engress_t *engress)
{
    /*
     * Only after the tick reaches this value can syn be retransmitted.
     */
    engress->tick_id = g_tick->ops->get_tick() + g_fack_tcp->cfg.syn_retrans_time;
}

static inline void __engress_tcp_establish_set_tick_id(session_engress_t *engress)
{
    uint16_t                establish_time;

    establish_time = g_fack_tcp->cfg.establish_time;

    if (establish_time == 0) {
        /*
         * If it's 0, Always establish
         */
        engress->tick_id = 0;
    } else {
        engress->tick_id = g_tick->ops->get_tick() + establish_time;
    }
}

static inline void __engress_tcp_fin_reset_tick_id(session_engress_t *engress)
{
    engress->tick_id = g_tick->ops->get_tick() + g_fack_tcp->cfg.fin_retrans_time;
}

static inline void __engress_tcp_close_set_tick_id(session_engress_t *engress)
{
    if (g_fack_tcp->cfg.close_wait_time == 0) {
        /*
         * If it's 0, Always establish
         */
        engress->tick_id = 0;

    } else {
        engress->tick_id = g_tick->ops->get_tick() + g_fack_tcp->cfg.close_wait_time;
    }
}

static inline void __tcp_change_state(session_engress_t *engress, 
        client_instance_context_t *ctx, spate_tcp_state_e new_state)
{
    client_stat_info_session_t      *sess;

    if (engress->state == new_state) {
        return;
    }

    sess = &ctx->stat_info.session;

    switch (engress->state) {
        case ST_IDLE:
            sess->idle--;
            break;

        case ST_SYN_SEND:
            sess->syn_send--;
            break;

        case ST_ESTABLISH:
            sess->establish--;
            break;

        case ST_FIN_SEND:
            sess->fin_send--;
            break;

        case ST_CLOSE:
            sess->closed--;
            break;

        default:
            return;
    }

    switch (new_state) {
        case ST_IDLE:
            sess->idle++;
            break;

        case ST_SYN_SEND:
            sess->syn_send++;
            break;

        case ST_ESTABLISH:
            sess->establish++;
            break;

        case ST_FIN_SEND:
            sess->fin_send++;
            break;

        case ST_CLOSE:
            sess->closed++;
            engress->retrans = 0;
            __engress_tcp_close_set_tick_id(engress);
            break;

        default:
            return;
    }

    engress->state = new_state;
}



static inline session_engress_t *__engress_tcp_update_idle(session_engress_t *engress, 
        client_instance_context_t *ctx)
{
    //engress->state    = ST_SYN_SEND;
    __tcp_change_state(engress, ctx, ST_SYN_SEND);
    engress->retrans  = 0;
    engress->sequence = random32() & 0x00FFFFFF;

    __engress_tcp_syn_reset_tick_id(engress);

    return engress;
}

static inline session_engress_t *__engress_tcp_handle_rst(session_engress_t *engress,
        client_instance_context_t *ctx)
{
    __tcp_change_state(engress, ctx, ST_CLOSE);
    return NULL;
}

static inline session_engress_t *__engress_tcp_update_synsend(session_engress_t *engress,
        client_instance_context_t *ctx)
{
    session_ingress_t       *ingress;
    uint32_t                sess_index;

    sess_index = engress - s_session_mgr->table.ses;
    ingress    = &s_session_mgr->table.sis[sess_index];

    if (ingress->tcp.syn_recv) {
        //engress->state   = ST_ESTABLISH;
        __tcp_change_state(engress, ctx, ST_ESTABLISH);
        engress->retrans = 0;
        __engress_tcp_establish_set_tick_id(engress);
        return engress;
    }

    if (ingress->tcp.rst_recv) {
        return __engress_tcp_handle_rst(engress, ctx);
    }

    if (g_tick->ops->get_tick() >= engress->tick_id) {
        /*
         * retransmit syn
         */
        __engress_tcp_syn_reset_tick_id(engress);
        engress->retrans = 1;

        return engress;
    };

    /*
     * retransmit cold time
     */
    return NULL;
}

static inline session_engress_t *__engress_tcp_update_establish(session_engress_t *engress, 
        client_instance_context_t *ctx)
{
    if (engress->tick_id && g_tick->ops->get_tick() >= engress->tick_id) {

        //engress->state = ST_FIN_SEND;
        __tcp_change_state(engress, ctx, ST_FIN_SEND);
        __engress_tcp_fin_reset_tick_id(engress);
    }

    return engress;
}

static inline session_engress_t *__engress_tcp_update_finsend(session_engress_t *engress,
        client_instance_context_t *ctx)
{
    session_ingress_t       *ingress;
    uint32_t                sess_index;

    sess_index = engress - s_session_mgr->table.ses;
    ingress = &s_session_mgr->table.sis[sess_index];

    if (ingress->tcp.fin_recv) {
        //engress->state   = ST_CLOSE;
        __tcp_change_state(engress, ctx, ST_CLOSE);
        return NULL;
    }

    if (g_tick->ops->get_tick() >= engress->tick_id) {
        __engress_tcp_fin_reset_tick_id(engress);
        engress->retrans = 1;
        return engress;
    }

    return NULL;
}

static inline void __engress_tcp_update_reset_idle(session_engress_t *engress, 
        client_instance_context_t *ctx)
{
    session_ingress_t       *ingress;
    uint32_t                sess_index;

    sess_index = engress - s_session_mgr->table.ses;
    ingress = &s_session_mgr->table.sis[sess_index];

    ingress->uint_val = 0;

    //engress->state    = ST_IDLE;
    __tcp_change_state(engress, ctx, ST_IDLE);
    engress->retrans  = 0;
    engress->tick_id  = 0;

}

static inline session_engress_t *__engress_tcp_update_close(session_engress_t *engress, 
        client_instance_context_t *ctx)
{
    if (engress->tick_id && g_tick->ops->get_tick() >= engress->tick_id) {
        __engress_tcp_update_reset_idle(engress, ctx);
    }

    return NULL;
}

static inline session_engress_t *__session_generate_update_tcp_with_split(
        session_engress_t *engress, client_instance_context_t *ctx)
{
    switch (engress->state) {
        case ST_IDLE:
            return __engress_tcp_update_idle(engress, ctx);
            break;

        case ST_SYN_SEND:
            return __engress_tcp_update_synsend(engress, ctx);
            break;

        case ST_ESTABLISH:
            return __engress_tcp_update_establish(engress, ctx);
            break;

        case ST_FIN_SEND:
            return __engress_tcp_update_finsend(engress, ctx);
            break;

        case ST_CLOSE:
            return __engress_tcp_update_close(engress, ctx);
            break;

        default:
            return engress;
    }

    return engress;
}

static inline session_engress_t *__session_generate_update_tcp_only_data(
        session_engress_t *engress)
{
    switch (engress->state) {
        case ST_ESTABLISH:
            return engress;
            break;

        default:
            return NULL;
    }

    return NULL;
}


session_engress_t *session_generate_update_tcp(session_engress_t *engress, 
        client_instance_context_t *ctx)
{
    if (g_session->cfg.table_split_by_worker) {
        return __session_generate_update_tcp_with_split(engress, ctx);

    } else {
        if (ctx->base.worker_id == 0) {
            return __session_generate_update_tcp_with_split(engress, ctx);

        } else {
            return __session_generate_update_tcp_only_data(engress);

        }
    }
}

/*
session_engress_t *session_generate_update_tcp_graceful(session_engress_t *engress, 
        client_instance_context_t *ctx)
{
}
*/
