/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_UTILS_H__
#define __EBPF_SPATE_UTILS_H__



#include "ebpf_include.h"
#include "ebpf_spate_export.h"



static __inline int __ebpf_host_is_my_ip(spate_ebpf_host_config_t *host_cfg,  uint32_t ip)
{
    return __spate_cfg_ip_is_contain(&host_cfg->host_ip, ip);
}


static __inline int __ebpf_spate_vxlan_underlay_info(spate_vxlan_underlay_info_t *ui, 
        char *underlay, uint16_t len, struct xdp_md *ctx)
{
    void *data_end = (void *)(long)ctx->data_end;
    uint16_t            underlay_len;
    uint16_t            min_overlay_len;
    uint16_t            iphdr_len;
    ipv4_hdr_t          *iphdr;
    udp_hdr_t           *udp;

    underlay_len = sizeof(ipv4_hdr_t) + sizeof(udp_hdr_t) + sizeof(vxlan_hdr_t);
    min_overlay_len = sizeof(ipv4_hdr_t) + sizeof(udp_hdr_t) + SPATE_MIN_PAYLOAD;

    if (len < underlay_len + min_overlay_len) {
        return -1;
    }

    iphdr     = (ipv4_hdr_t *)(underlay);
    iphdr_len = __spate_iphdr_len(iphdr);

    udp       = (udp_hdr_t *)((char *)iphdr + iphdr_len);

    if ((void *)udp + sizeof(udp_hdr_t) > data_end) {
        return -1;
    }

    if (iphdr->next_proto_id != IPPROTO_UDP) {
        return -1;
    }

    if (udp->dst_port != ___constant_swab16(4789)) {
        return -1;
    }

    ui->underlay_len = sizeof(udp_hdr_t) + sizeof(vxlan_hdr_t) + iphdr_len;
    
    if (ui->underlay_len > len) {
        return -1;
    }

    ui->underlay_sip = iphdr->src_addr;
    ui->underlay_dip = iphdr->dst_addr;
    return 0;
}


#endif /* __EBPF_SPATE_UTILS_H__ */
