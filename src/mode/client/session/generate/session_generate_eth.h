/*
 * Rodzhang
 *
 */

#ifndef __SESSION_GENERATE_ETH_H__
#define __SESSION_GENERATE_ETH_H__

#include <spate_core.h>
#include <spate_packet.h>
#include <spate_net.h>
#include <spate_hook.h>
#include <spate_plane.h>


static inline uint16_t __generate_ethhdr_get_len(void)
{
    if (__packet_is_vlan_enable()) {
        return sizeof(eth_hdr_t) + sizeof(vlan_hdr_t);
    } else {
        return sizeof(eth_hdr_t);
    }

}

static inline void __generate_ethhdr(eth_hdr_t *eth, uint16_t eth_len, const uint8_t *dmac)
{
    vlan_hdr_t              *vlan;

    memcpy(eth->d_addr, dmac, NP_ETH_ALEN);
    memcpy(eth->s_addr, __spate_netdev_mac_addr(), NP_ETH_ALEN);

    if (eth_len == sizeof(eth_hdr_t)+sizeof(vlan_hdr_t)) {
        /*
         * vlan
         */   
        vlan = (vlan_hdr_t *)(eth + 1);

        eth->ether_type = htons(NP_ETHER_TYPE_VLAN);
        vlan->vlan_tci  = htons(__packet_vlan_id_get());
        vlan->eth_proto = htons(NP_ETHER_TYPE_IPV4);

    } else {
        eth->ether_type = htons(NP_ETHER_TYPE_IPV4);
    }

}


#endif /* __SESSION_GENERATE_ETH_H__ */


