/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_CLIENT_RX_IP_H__
#define __EBPF_SPATE_CLIENT_RX_IP_H__


#include "ebpf_spate_client_dep.h"
#include "ebpf_spate_client_rx_icmp.h"
#include "ebpf_spate_client_rx_udp.h"
#include "ebpf_spate_client_rx_tcp.h"


static __inline int __ebpf_spate_client_rx_ip(ipv4_hdr_t *iph, uint16_t len, struct xdp_md *ctx, 
        spate_ebpf_client_config_t *cfg, spate_ebpf_client_stat_t *stat)
{
    void *data_end = (void *)(long)ctx->data_end;
    int                         ret;
    void                        *l4hdr;
    uint16_t                    l4len;

    if (unlikely(!__spate_is_iphdr_check_ok(iph, len))) {
        return XDP_PASS;
    }

    l4hdr = (char *)(iph + 1);
    l4len = len - sizeof(*iph);

    ret = XDP_PASS;

    switch (iph->next_proto_id) {
        case IPPROTO_UDP:
            if (iph->next_proto_id != cfg->session.proto) {
                return XDP_PASS;
            }
            if (l4hdr + sizeof(udp_hdr_t) + sizeof(spate_payload_t) > data_end) {
                return XDP_PASS;
            }
            ret = __ebpf_spate_client_rx_udp((udp_hdr_t*)l4hdr, l4len, iph, cfg, stat);
            break;

        case IPPROTO_TCP:
            if (iph->next_proto_id != cfg->session.proto) {
                return XDP_PASS;
            }
            if (l4hdr + sizeof(tcp_hdr_t) + sizeof(spate_payload_t) > data_end) {
                return XDP_PASS;
            }
            ret = __ebpf_spate_client_rx_tcp(iph, len, ctx, cfg, stat);
            break;
            
        case IPPROTO_ICMP:
            if (l4hdr + sizeof(icmp_hdr_t) > data_end) {
                return XDP_PASS;
            }
            ret = __ebpf_spate_client_rx_icmp((icmp_hdr_t*)l4hdr, l4len, iph, cfg);
            break;

        default:
            ret = XDP_PASS;
            break;
    }

    if (ret == XDP_TX) {
        __spate_iphdr_reverse_ip(iph);
    }

    return ret;
}


#endif /* __EBPF_SPATE_CLIENT_RX_IP_H__ */
