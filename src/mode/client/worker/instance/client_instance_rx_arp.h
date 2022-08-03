/*
 * Rodzhang
 *
 */

#ifndef __CLIENT_INSTANCE_RX_ARP_H__
#define __CLIENT_INSTANCE_RX_ARP_H__


#include <spate_core.h>
#include <spate_net.h>


int client_instance_rx_arp(eth_hdr_t *ethhdr, arp_hdr_t *arp, uint16_t arp_len);



#endif /* __CLIENT_INSTANCE_RX_ARP_H__ */
