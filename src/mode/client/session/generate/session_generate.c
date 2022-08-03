/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_packet.h>
#include <spate_net.h>
#include <spate_vxlan.h>
#include "session_generate.h"
#include "session_generate_vxlan.h"
#include "session_generate_eth.h"
#include "session_generate_ip.h"
#include "session_generate_update.h"
#include <spate_utils.h>


static inline uint16_t __generate_packet_data_without_encapsulation(client_instance_context_t *ctx,
        session_engress_t *engress, char *pkt_data, uint64_t now, uint32_t gen_code)
{
    char                    *ip_data;
    eth_hdr_t               *ethhdr;
    uint16_t                eth_len, ip_len;

    ethhdr  = (eth_hdr_t *)pkt_data;
    eth_len = __generate_ethhdr_get_len();

    ip_data = (char *)ethhdr + eth_len;

    ip_len  = __generate_packet_ip_data(ctx, engress, ip_data, now, gen_code);

    __generate_ethhdr(ethhdr, eth_len, __packet_dmac_addr_get());

    return eth_len + ip_len;
}

static inline uint16_t __generate_packet_data(client_instance_context_t *ctx,
        session_engress_t *engress, char *pkt_data, uint64_t now, uint32_t gen_code)
{
    if (unlikely(__vxlan_is_enable())) {
        return generate_vxlan_packet_data(ctx, engress, pkt_data, now, gen_code);
    } else {
        return __generate_packet_data_without_encapsulation(ctx, engress, pkt_data, now, gen_code);
    }
}

static inline session_engress_t *__session_generate_get_engress(uint32_t sess_idx, 
        client_instance_context_t *ctx)
{
    session_engress_t       *engress;

    ASSERT(sess_idx <= s_session_mgr->table.sess_nr);

    engress = &s_session_mgr->table.ses[sess_idx];

    return __session_generate_update(engress, ctx);
}


static inline void __session_roll_walk_next(session_roll_t *sr)
{
    if (sr->sess_idx_curr + 1 < sr->sess_idx_end) {
        sr->sess_idx_curr ++;
    } else {
        sr->sess_idx_curr = sr->sess_idx_begin;
    }
}

static uint16_t _session_generate_pkts_graceful(client_instance_context_t *ctx, 
        uint64_t now, char **pkts, uint16_t *lens, uint16_t pkt_nr)
{
    uint16_t                i, gen_nr;
    session_engress_t       *engress;
    session_roll_t          *sr;

    sr = &ctx->session_roll;
    
    if (unlikely(sr->sess_idx_begin == sr->sess_idx_end)) {
        return 0;
    }

    ASSERT(sr->sess_idx_curr>=sr->sess_idx_begin && sr->sess_idx_curr<sr->sess_idx_end);

    gen_nr = 0;

    for (i=0; i<pkt_nr; ++i) {

        engress = &s_session_mgr->table.ses[sr->sess_idx_curr];

        lens[gen_nr] = __generate_packet_data(ctx, engress, pkts[gen_nr], now, SESSION_GEN_TCP_RST);

        gen_nr++;

        __session_roll_walk_next(sr);
    }

    return gen_nr;
}

static inline uint16_t __session_generate_pkts(client_instance_context_t *ctx, 
        uint64_t now, char **pkts, uint16_t *lens, uint16_t pkt_nr)
{
    uint16_t                i, gen_nr;
    session_engress_t       *engress;
    session_roll_t          *sr;

    sr = &ctx->session_roll;
    
    if (unlikely(sr->sess_idx_begin == sr->sess_idx_end)) {
        return 0;
    }

    ASSERT(sr->sess_idx_curr>=sr->sess_idx_begin && sr->sess_idx_curr<sr->sess_idx_end);

    gen_nr = 0;

    for (i=0; i<pkt_nr; ++i) {

        engress = __session_generate_get_engress(sr->sess_idx_curr, ctx);

        if (likely(engress)) {
            lens[gen_nr] = __generate_packet_data(ctx, engress, pkts[gen_nr], now, 0);

            gen_nr++;
        }

        __session_roll_walk_next(sr);
    }

    return gen_nr;
}


uint16_t session_generate_pkts(client_instance_context_t *ctx, uint64_t now, 
        char **pkts, uint16_t *lens, uint16_t pkt_nr)
{
    if (unlikely(s_session_mgr->graceful.graceful_active)) {
        return _session_generate_pkts_graceful(ctx, now, pkts, lens, pkt_nr);
    } else {
        return __session_generate_pkts(ctx, now, pkts, lens, pkt_nr);
    }
}


int session_generate_pkt(client_instance_context_t *ctx, uint64_t now,
        session_generate_ctrl_t *sgc, char *pkt, uint16_t *len)
{
    session_engress_t       *engress;

    if (sgc->sess_index >= s_session_mgr->table.sess_nr) {
        return -1;
    }

    if (sgc->generate_code >= SESSION_GEN_MAX) {
        return -1;
    }

    engress = &s_session_mgr->table.ses[sgc->sess_index];

    *len = __generate_packet_data(ctx, engress, pkt, now, sgc->generate_code);

    return 0;
}
