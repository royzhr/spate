/*
 * Rodzhang
 *
 */

#include "client_instance_rx_icmp.h"
#include <spate_host.h>
#include <spate_plane.h>


int client_instance_rx_icmp(eth_hdr_t *ethhdr, ipv4_hdr_t *iphdr, uint16_t ip_len)
{
    icmp_hdr_t                  *icmp;
    uint16_t                    icmp_len;

    if (!__host_is_icmp_enable()) {
        return INSTANCE_RX_RET_DROP;
    }

    if (!__host_is_my_ip(iphdr->dst_addr)) {
        return INSTANCE_RX_RET_DROP;
    }

    icmp     = (icmp_hdr_t *)(iphdr + 1);
    icmp_len = ip_len - sizeof(*iphdr);

    if (!__spate_is_icmphdr_check_ok(icmp, icmp_len)) {
        return INSTANCE_RX_RET_DROP;
    }

    __spate_icmphdr_modify_to_replay(icmp);

    __spate_iphdr_reverse_ip(iphdr);

    __spate_ethhdr_reverse_mac(ethhdr, __spate_netdev_mac_addr());

    return INSTANCE_RX_RET_TX;
}


