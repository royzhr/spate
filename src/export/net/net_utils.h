/*
 * Rodzhang
 *
 */

#ifndef __NET_UTILS_H__
#define __NET_UTILS_H__


#include "net_proto/net_proto.h"
#include "net_eth.h"
#include "net_arp.h"
#include "net_icmp.h"


static __inline uint16_t __spate_iphdr_len(ipv4_hdr_t *iphdr)
{
    return (iphdr->version_ihl & 0x0F) * 4;
}

static __inline int __spate_is_iphdr_check_ok(ipv4_hdr_t *iphdr, uint16_t len)
{
    if (unlikely(len < sizeof(*iphdr))) {
        return 0;
    }

    if (unlikely(len < __spate_iphdr_len(iphdr))) {
        return 0;
    }

    if (unlikely((iphdr->version_ihl & 0x0F0) != 0x40)) {
        return 0;
    }

    return  1;
}


static __inline uint16_t __spate_tcphdr_len(tcp_hdr_t *tcp)
{
    return ((tcp->data_off & 0x0F0) >> 2);
}


static __inline int __spate_is_tcphdr_check_ok(tcp_hdr_t *tcp, uint16_t len)
{
    if (unlikely(len < sizeof(*tcp))) {
        return 0;
    }

    if (unlikely(len < __spate_tcphdr_len(tcp))) {
        return 0;
    }

    return 1;
}


static __inline int __spate_is_udphdr_check_ok(udp_hdr_t *udp, uint16_t len)
{
    if (unlikely(len < sizeof(*udp))) {
        return 0;
    }

    return 1;
}


static __inline void __spate_iphdr_reverse_ip(ipv4_hdr_t *iphdr)
{
    uint32_t                    tmp;

    memcpy(&tmp, &iphdr->src_addr, sizeof(uint32_t));
    memcpy(&iphdr->src_addr, &iphdr->dst_addr, sizeof(uint32_t));
    memcpy(&iphdr->dst_addr, &tmp, sizeof(uint32_t));
}

static inline void __server_udphdr_reverse_port(udp_hdr_t *udp)
{
    uint16_t                tmp;

    memcpy(&tmp, &udp->src_port, sizeof(uint16_t));
    memcpy(&udp->src_port, &udp->dst_port, sizeof(uint16_t));
    memcpy(&udp->dst_port, &tmp, sizeof(uint16_t));
}


static __inline void __spate_ethhdr_reverse_mac(eth_hdr_t *ethhdr, const uint8_t *smac)
{
    memcpy(ethhdr->d_addr, ethhdr->s_addr,  NP_ETH_ALEN);
    memcpy(ethhdr->s_addr, smac,            NP_ETH_ALEN);
}


typedef struct {
    uint16_t            underlay_len;

    /*
     * net order
     */
    uint32_t            underlay_sip;
    uint32_t            underlay_dip;

} spate_vxlan_underlay_info_t;

/*
 * underlay length without underlay's ethhdr
 * Param:
 * @ui      : [Ouput]
 * @underlay: [Input]
 * @len     : [Input]
 *
 * Return Value:
 * 0        : vxlan packet
 * <0       : Not vxlan packet
 */
static __inline int __spate_vxlan_underlay_info(spate_vxlan_underlay_info_t *ui, 
        char *underlay, uint16_t len)
{
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

    if (iphdr->next_proto_id != IPPROTO_UDP) {
        return -1;
    }

    if (__ntohs(udp->dst_port) != 4789) {
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


#endif /* __NET_UTILS_H__ */
