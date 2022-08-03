/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_SERVER_RX_UDP_H__
#define __EBPF_SPATE_SERVER_RX_UDP_H__


#include "ebpf_spate_server_dep.h"
#include "ebpf_spate_server_rx_payload.h"
#include "ebpf_spate_server_utils.h"

static __inline int __ebpf_spate_server_rx_udp(udp_hdr_t *udp, uint16_t len, ipv4_hdr_t *iph,
        spate_ebpf_server_config_t *cfg, server_stat_info_t *stat)
{
    int                         ret;
    spate_payload_t             *ps;
    uint16_t                    payload_len;

    if (!cfg->listen.proto_udp) {
        return XDP_PASS;
    }

    if (!__ebpf_is_server_listen_ip(cfg, iph->dst_addr)) {
        return XDP_PASS;
    }

    if (!__ebpf_is_server_listen_port(cfg, udp->dst_port)) {
        return XDP_PASS;
    }

    ps          = (spate_payload_t *)(udp + 1);
    payload_len = len - sizeof(*udp);

    ret = __ebpf_spate_server_rx_payload(ps, payload_len);

    if (likely(ret == XDP_TX)) {

#ifdef SPATE_EBPF_DEBUG
        char            fmt4[] = "spate server tx udp ";
        bpf_trace_printk(fmt4, sizeof(fmt4));
#endif
        __server_udphdr_reverse_port(udp);

        stat->traffic.rx_pkts ++;
        stat->traffic.tx_pkts ++;
    }

    return ret;
}



#endif /* __EBPF_SPATE_SERVER_RX_UDP_H__ */
