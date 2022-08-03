/*
 * Rodzhang
 *
 */

#ifndef __NP_ETHER_H__
#define __NP_ETHER_H__

#include "np_types.h"

#define NP_ETH_ALEN         6

typedef struct {
	
    unsigned char	d_addr[NP_ETH_ALEN];	/* destination eth addr	*/
	unsigned char	s_addr[NP_ETH_ALEN];	/* source ether addr	*/
	uint16_t		ether_type;		   /* packet type ID field	*/

} __attribute__((packed)) eth_hdr_t;


#define NP_ETHER_TYPE_IPV4 0x0800 /**< IPv4 Protocol. */
#define NP_ETHER_TYPE_ARP  0x0806 /**< Arp Protocol. */
#define NP_ETHER_TYPE_VLAN 0x8100 /**< IEEE 802.1Q VLAN tagging. */
#define NP_ETHER_TYPE_MPLS 0x8847 /**< MPLS ethertype. */




#endif /* __NP_ETHER_H__ */
