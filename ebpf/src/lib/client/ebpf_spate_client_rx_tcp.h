/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_CLIENT_RX_TCP_H__
#define __EBPF_SPATE_CLIENT_RX_TCP_H__


#include "ebpf_spate_client_dep.h"
#include "ebpf_spate_client_utils.h"
#include "ebpf_spate_client_rx_payload.h"


static __inline int __is_ebpf_spate_client_tcp_can_offload(tcp_hdr_t *tcp)
{
    if (tcp->tcp_flags & NP_TCP_SYN_FLAG) {
        return 0;
    }

    if (tcp->tcp_flags & NP_TCP_FIN_FLAG) {
        return 0;
    }

    return 1;
}


static __inline int __ebpf_spate_client_rx_tcp(ipv4_hdr_t *iph, uint16_t l3_len, struct xdp_md *ctx,
        spate_ebpf_client_config_t *cfg, spate_ebpf_client_stat_t *stat) 
{
    void *data_end = (void *)(long)ctx->data_end;
    tcp_hdr_t                   *tcp;
    spate_payload_t             *ps;
    uint16_t                    payload_len, tcphdr_len;
    int                         ret;

    tcp = (tcp_hdr_t *)(iph + 1);

    tcphdr_len  = __spate_tcphdr_len(tcp);

    if ((void*)tcp+tcphdr_len+sizeof(spate_payload_t) > data_end ) {
        return XDP_PASS;
    }

    if (!__ebpf_is_client_sip(cfg, iph->dst_addr)) {
        return XDP_PASS;
    }

    if (!__ebpf_is_client_sport(cfg, tcp->dst_port)) {
        return XDP_PASS;
    }

#ifdef SPATE_EBPF_DEBUG
    char            fmt4[] = "spate client recv tcp ";
    bpf_trace_printk(fmt4, sizeof(fmt4));
#endif

    if (!__is_ebpf_spate_client_tcp_can_offload(tcp)) {
        /*
         * If the tcp-packet cant offload, it need to be sent to user-space
         */
#ifdef SPATE_EBPF_DEBUG
        char            fmt2[] = "spate client recv tcp send to user-space";
        bpf_trace_printk(fmt2, sizeof(fmt2));
#endif
        return XDP_PASS;
    }

    ps          = (spate_payload_t *)((char *)tcp + tcphdr_len);
    payload_len = l3_len - sizeof(*iph) - tcphdr_len;

    ret = __ebpf_spate_client_rx_payload(ps, payload_len, stat);

    return ret;
}



#endif /* __EBPF_SPATE_CLIENT_RX_TCP_H__ */
