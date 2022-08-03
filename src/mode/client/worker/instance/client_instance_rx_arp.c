/*
 * Rodzhang
 *
 */


#include "client_instance_rx_arp.h"
#include <spate_host.h>
#include <spate_plane.h>


int client_instance_rx_arp(eth_hdr_t *ethhdr, arp_hdr_t *arp, uint16_t arp_len)
{
    if (!__host_is_arp_enable()) {
        return INSTANCE_RX_RET_DROP;
    } 

    if (!__spate_is_arphdr_check_ok(arp, arp_len)) {
        return INSTANCE_RX_RET_DROP;
    }

    if (!__host_is_my_ip(arp->arp_data.arp_tip)) {
        return INSTANCE_RX_RET_DROP;
    }

    __spate_arphdr_modify_to_replay(arp, __spate_netdev_mac_addr());

    __spate_ethhdr_reverse_mac(ethhdr, __spate_netdev_mac_addr());

    return INSTANCE_RX_RET_TX;
}




