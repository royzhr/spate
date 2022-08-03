/*
 * Rodzhang
 *
 */

#ifndef __NP_ARP_H__
#define __NP_ARP_H__

#include "np_types.h"
#include "np_ether.h"

typedef struct {
	uint8_t         arp_sha[NP_ETH_ALEN];  /**< sender hardware address */
	uint32_t        arp_sip;  /**< sender IP address */
	uint8_t         arp_tha[NP_ETH_ALEN];  /**< target hardware address */
	uint32_t        arp_tip;  /**< target IP address */
} __attribute__((packed)) arp_ipv4_t;

typedef struct {
	uint16_t arp_hardware;    /* format of hardware address */
#define NP_ARP_HRD_ETHER     1  /* ARP Ethernet address format */

	uint16_t arp_protocol;    /* format of protocol address */
	uint8_t  arp_hlen;    /* length of hardware address */
	uint8_t  arp_plen;    /* length of protocol address */
	uint16_t arp_opcode;     /* ARP opcode (command) */
#define	NP_ARP_OP_REQUEST    1 /* request to resolve address */
#define	NP_ARP_OP_REPLY      2 /* response to previous request */
#define	NP_ARP_OP_REVREQUEST 3 /* request proto addr given hardware */
#define	NP_ARP_OP_REVREPLY   4 /* response giving protocol address */
#define	NP_ARP_OP_INVREQUEST 8 /* request to identify peer */
#define	NP_ARP_OP_INVREPLY   9 /* response identifying peer */

	arp_ipv4_t  arp_data;

} __attribute__((packed)) arp_hdr_t;


#endif /* __NP_ARP_H__ */


