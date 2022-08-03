/*
 * Rodzhang
 *
 */

#include "session_ops.h"
#include "session_mgr.h"
#include "session_assign.h"
#include "generate/session_generate.h"


static uint32_t _session_get_nr(void)
{
    return s_session_mgr->table.sess_nr;
}

static void _session_on_tcp_update(uint32_t sess_idx, tcp_hdr_t *tcp)
{
    session_ingress_t       *ingress;

    if (sess_idx >= s_session_mgr->table.sess_nr) {
        return;
    }

    ingress = &s_session_mgr->table.sis[sess_idx];

    if (tcp->tcp_flags & NP_TCP_SYN_FLAG) {
        ingress->tcp.syn_recv = 1;

    } else if (tcp->tcp_flags & NP_TCP_FIN_FLAG) {
        ingress->tcp.fin_recv = 1;
    }

}

static inline int __session_lookup(uint32_t *idx, uint32_t sip, 
        uint32_t dip, uint16_t sport, uint16_t dport)
{
    return s_session_mgr->lookup->vptr->lookup(s_session_mgr->lookup, 
            idx, sip, dip, sport, dport);
}

static void _session_on_recv_tcp_rst(ipv4_hdr_t *iphdr, tcp_hdr_t *tcp)
{
    uint32_t                sip, dip;
    uint16_t                sport, dport;
    uint32_t                sess_idx;
    session_ingress_t       *ingress;

    if (!s_session_mgr->lookup) {
        return;
    }

    sip   = ntohl(iphdr->dst_addr);
    dip   = ntohl(iphdr->src_addr);
    sport = ntohs(tcp->dst_port);
    dport = ntohs(tcp->src_port);

    if (__session_lookup(&sess_idx, sip, dip, sport, dport) < 0) {
        return;
    }

    ingress = &s_session_mgr->table.sis[sess_idx];

    ingress->tcp.rst_recv = 1;
}


const session_ops_t c_session_ops = {
    .generate_pkts       = session_generate_pkts,
    .generate_pkt        = session_generate_pkt,
    .get_session_nr      = _session_get_nr,
    .on_tcp_update       = _session_on_tcp_update,
    .on_recv_tcp_rst     = _session_on_recv_tcp_rst,
    .assign_to_worker    = session_assign_to_worker,
};


