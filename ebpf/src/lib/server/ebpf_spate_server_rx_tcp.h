/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_SERVER_RX_TCP_H__
#define __EBPF_SPATE_SERVER_RX_TCP_H__


#include "ebpf_spate_server_dep.h"
#include "ebpf_spate_server_rx_payload.h"
#include "ebpf_spate_server_utils.h"

static __inline uint16_t __ebpf_server_tcphdr_addack_cksum(tcp_hdr_t *tcp)
{
    uint16_t                cksum;

    if (tcp->cksum < 0x1000) {
        cksum =  tcp->cksum - 0x1000 - 1;
    } else {

        cksum =  tcp->cksum - 0x1000;
    }

    return cksum;
}

static __inline void __ebpf_server_tcphdr_update(tcp_hdr_t *tcp, ipv4_hdr_t *iphdr)
{
    uint16_t                tmp;

    memcpy(&tmp, &tcp->src_port, sizeof(uint16_t));
    memcpy(&tcp->src_port, &tcp->dst_port, sizeof(uint16_t));
    memcpy(&tcp->dst_port, &tmp, sizeof(uint16_t));

    if (tcp->tcp_flags & NP_TCP_ACK_FLAG) {
        return;
    }

    tcp->tcp_flags = tcp->tcp_flags | NP_TCP_ACK_FLAG;

    tcp->cksum = __ebpf_server_tcphdr_addack_cksum(tcp);
}

static __inline int __ebpf_spate_server_rx_tcp(ipv4_hdr_t *iph, uint16_t l3_len, struct xdp_md *ctx,
        spate_ebpf_server_config_t *cfg, server_stat_info_t *stat) 
{
    void *data_end = (void *)(long)ctx->data_end;
    tcp_hdr_t                   *tcp;
    spate_payload_t             *ps;
    uint16_t                    payload_len, tcphdr_len;
    int                         ret;

    if (!cfg->listen.proto_tcp) {
        return XDP_PASS;
    }

    if (!__ebpf_is_server_listen_ip(cfg, iph->dst_addr)) {
        return XDP_PASS;
    }

    tcp = (tcp_hdr_t *)(iph + 1);

    if (!__ebpf_is_server_listen_port(cfg, tcp->dst_port)) {
        return XDP_PASS;
    }

    tcphdr_len  = __spate_tcphdr_len(tcp);

    if ((void*)tcp+tcphdr_len+sizeof(spate_payload_t) > data_end ) {
        return XDP_PASS;
    }

    ps          = (spate_payload_t *)((char *)tcp + tcphdr_len);
    payload_len = l3_len - sizeof(*iph) - tcphdr_len;

    ret = __ebpf_spate_server_rx_payload(ps, payload_len);

    if (likely(ret == XDP_TX)) {
        __ebpf_server_tcphdr_update(tcp, iph);

        stat->traffic.rx_pkts ++;
        stat->traffic.tx_pkts ++;
    }

    return ret;
}



#endif /* __EBPF_SPATE_SERVER_RX_TCP_H__ */
