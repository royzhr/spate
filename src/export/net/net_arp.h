/*
 * Rodzhang
 *
 */

#ifndef __NET_ARP_H__
#define __NET_ARP_H__


#include "net_proto/net_proto.h"


static __inline int __spate_is_arphdr_check_ok(arp_hdr_t *arp, uint16_t len)
{
    if (len < sizeof(*arp)) {
        return 0;
    }

    if (__ntohs(arp->arp_hardware) != 1) {
        return 0;
    }
    
    if (__ntohs(arp->arp_protocol) != NP_ETHER_TYPE_IPV4) {
        return 0;
    }

    if (arp->arp_hlen != 6) {
        return 0;
    }

    if (arp->arp_plen != 4) {
        return 0;
    }

    if (__ntohs(arp->arp_opcode) != NP_ARP_OP_REQUEST) {
        return 0;
    }

    return 1;
}


static __inline void __spate_arphdr_modify_to_replay(arp_hdr_t *arp, const uint8_t *my_mac)
{
    uint32_t                server_ip;

    server_ip = arp->arp_data.arp_tip;

    memcpy(&arp->arp_data.arp_tha, &arp->arp_data.arp_sha, NP_ETH_ALEN);
    memcpy(&arp->arp_data.arp_tip, &arp->arp_data.arp_sip, 4);

    memcpy(&arp->arp_data.arp_sha, my_mac, NP_ETH_ALEN);
    memcpy(&arp->arp_data.arp_sip, &server_ip, 4);


    arp->arp_opcode = __htons(NP_ARP_OP_REPLY);
}




#endif /* __NET_ARP_H__ */
