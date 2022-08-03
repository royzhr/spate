/*
 * Rodzhang
 *
 */

#ifndef __NET_ETH_H__
#define __NET_ETH_H__


#include <stdint.h>
#include "net_proto/net_proto.h"


/*
 * @ ethhdr  :   eth-header
 * @ len     :   packet's data len
 * @ eth_type [output]  : host byte order
 * @ eth_len  [output]  : eth-header's len
 *
 * @Return Val:
 * 0    : succuess
 * <0   : failed
 *
 */
static __inline int __spate_ethhdr_parse(eth_hdr_t *ethhdr, uint16_t len, 
        uint16_t *ether_type, uint16_t *eth_len)

{
    vlan_hdr_t          *vlan;

    *ether_type = __ntohs(ethhdr->ether_type);

    if (*ether_type == NP_ETHER_TYPE_VLAN) {
    
        vlan = (vlan_hdr_t *)(ethhdr + 1);

        *eth_len = sizeof(*ethhdr) + sizeof(*vlan);

        *ether_type = __ntohs(vlan->eth_proto);

    } else {
    
        *eth_len = sizeof(*ethhdr);
    }

    if (unlikely(len <= *eth_len)) {
        return -1;
    }

    return 0;
}

static __inline int __spate_is_broadcast_ether_addr(uint8_t *mac)
{
    if (mac[0] == 0xFF && mac[1] == 0xFF) {
        return 1;
    } else {
        return 0;
    }
}

static __inline int __spate_is_same_mac(const uint8_t *m1, const uint8_t *m2)
{
    if (m1[0]==m2[0] && m1[1]==m2[1] && m1[2]==m2[2] &&
            m1[3]==m2[3] && m1[4]==m2[4] && m1[5]==m2[5]) {
        return 1;
    }

    return 0;
}

static __inline int __spate_is_ethhdr_dmac_myself(eth_hdr_t *ethhdr, const uint8_t *my_mac)
{
    if (__spate_is_same_mac(ethhdr->d_addr, my_mac)) {
        return 1;
    }

    if (__spate_is_broadcast_ether_addr(ethhdr->d_addr)) {
        return 1;
    }

    return 0;
}






#endif /* __NET_ETH_H__ */
