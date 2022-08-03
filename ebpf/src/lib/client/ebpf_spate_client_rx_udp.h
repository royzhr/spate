/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_CLIENT_RX_UDP_H__
#define __EBPF_SPATE_CLIENT_RX_UDP_H__


#include "ebpf_spate_client_dep.h"
#include "ebpf_spate_client_utils.h"
#include "ebpf_spate_client_rx_payload.h"


static __inline int __ebpf_spate_client_rx_udp(udp_hdr_t *udp, uint16_t len, ipv4_hdr_t *iph,
        spate_ebpf_client_config_t *cfg, spate_ebpf_client_stat_t *stat)
{
    int                         ret;
    spate_payload_t             *ps;
    uint16_t                    payload_len;


    if (!__ebpf_is_client_sip(cfg, iph->dst_addr)) {
        return XDP_PASS;
    }

    if (!__ebpf_is_client_sport(cfg, udp->dst_port)) {
        return XDP_PASS;
    }

#ifdef SPATE_EBPF_DEBUG
    char            fmt4[] = "spate client recv udp ";
    bpf_trace_printk(fmt4, sizeof(fmt4));
#endif

    ps          = (spate_payload_t *)(udp + 1);
    payload_len = len - sizeof(*udp);

    ret = __ebpf_spate_client_rx_payload(ps, payload_len, stat);

    return ret;
}



#endif /* __EBPF_SPATE_CLIENT_RX_UDP_H__ */
