/*
 * Rodzhang
 *
 */

#include "client_instance_context_method.h"

#include <spate_core.h>
#include <spate_main.h>
#include <spate_session.h>
#include <spate_utils.h>
#include "client_instance_context_method.h"
#include "client_instance_ftbl.h"
#include "../client_worker_traffic_ctrl.h"

#include <spate_todo.h>




static void _client_instance_context_stat_constructor(client_instance_context_t *ctx)
{
    client_stat_info_t      *cs;

    cs = &ctx->stat_info;

    cs->session.idle = ctx->session_roll.sess_idx_end - ctx->session_roll.sess_idx_begin;
}

int  client_instance_context_constructor(client_instance_context_t *ctx, 
        uint16_t worker_id, uint16_t worker_nr)
{
    if (instance_context_constructor(&ctx->base, worker_id) < 0) {
        return -1;
    }

    if (g_session->ops->assign_to_worker(&ctx->session_roll, worker_id, worker_nr) < 0) {
        return -1;
    }

    client_traffic_controller_setting(&ctx->tc);

    LOGI("assign worker%u: %u->%u, %p, brust=%u, wait=%lu", 
            worker_id, ctx->session_roll.sess_idx_begin,
            ctx->session_roll.sess_idx_end, 
            ctx, ctx->tc.tx_burst_nr, ctx->tc.tx_burst_cycles);

    _client_instance_context_stat_constructor(ctx);

    ctx->fptr = &c_client_instance_ftbl;

    return 0;
}

void client_instance_context_destructor(client_instance_context_t *ctx)
{
    ctx->fptr = NULL;

    instance_context_destructor(&ctx->base);
}



