/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_SERVER_RX_VXLAN_H__
#define __EBPF_SPATE_SERVER_RX_VXLAN_H__


#include "ebpf_spate_server_dep.h"
#include "ebpf_spate_server_rx_ip.h"


static __inline int __ebpf_spate_server_vxlan_overlay(char *overlay, uint16_t overlay_len, 
        struct xdp_md *ctx, spate_ebpf_server_config_t *cfg, server_stat_info_t *stat)
{
    void *data_end = (void *)(long)ctx->data_end;
    eth_hdr_t                       *eth;
    int                             ret;

    eth = (eth_hdr_t *)overlay;

    if ((void*)eth + sizeof(eth_hdr_t) + sizeof(ipv4_hdr_t) > data_end) {
        return XDP_PASS;
    }

    if (eth->ether_type != ___constant_swab16(NP_ETHER_TYPE_IPV4)) {
        return XDP_PASS;
    }

    ret = __ebpf_spate_server_rx_ip((ipv4_hdr_t*)(eth+1), overlay_len-sizeof(eth_hdr_t), 
            ctx, cfg, stat);

    if (ret == XDP_TX) {
        __spate_ethhdr_reverse_mac(eth, cfg->device.mac_addr);
    }

    return ret;
}

static __inline int __ebpf_spate_server_vxlan_underlay(char *underlay, uint16_t underlay_len,
        struct xdp_md *ctx, spate_ebpf_server_config_t *cfg)
{
    void *data_end = (void *)(long)ctx->data_end;
    ipv4_hdr_t                      *iph;

    iph = (ipv4_hdr_t *)underlay;

    if ((void*)iph + sizeof(ipv4_hdr_t) > data_end) {
        return XDP_PASS;
    }

    __spate_iphdr_reverse_ip(iph);

    return XDP_TX;
}

static __inline int __ebpf_spate_server_rx_vxlan(char *underlay_iph, uint16_t len, 
        struct xdp_md *ctx, spate_ebpf_server_config_t *cfg, server_stat_info_t *stat)
{
    void *data_end = (void *)(long)ctx->data_end;
    spate_vxlan_underlay_info_t     ui;
    uint16_t                        underlay_len;
    uint16_t                        overlay_len;
    char                            *underlay;
    char                            *overlay;
    int                             ret;

    if ((void*)underlay_iph + len > data_end) {
        
        return XDP_PASS;
    }

    underlay = underlay_iph;

    if (__ebpf_spate_vxlan_underlay_info(&ui, underlay, len, ctx) < 0) {
        /*
         * Not underlay
         */
        goto not_vxlan_packet;
    }

    underlay_len = ui.underlay_len;
    overlay      = underlay + underlay_len;
    overlay_len  = len - underlay_len;

    if (!__ebpf_is_server_vxlan_packet(cfg, &ui)) {
        goto not_vxlan_packet;
    }

    ret = __ebpf_spate_server_vxlan_overlay(overlay, overlay_len, ctx, cfg, stat);
    if (ret != XDP_TX) {
        return ret;
    }

    ret = __ebpf_spate_server_vxlan_underlay(underlay, underlay_len, ctx, cfg);

    return ret;

not_vxlan_packet:
    return __ebpf_spate_server_rx_ip((ipv4_hdr_t*)underlay_iph, len, ctx, cfg, stat);
}



#endif /* __EBPF_SPATE_SERVER_RX_VXLAN_H__ */
