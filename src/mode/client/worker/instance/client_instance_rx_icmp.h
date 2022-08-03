/*
 * Rodzhang
 *
 */

#ifndef __CLIENT_INSTANCE_RX_ICMP_H__
#define __CLIENT_INSTANCE_RX_ICMP_H__

#include <spate_core.h>
#include <spate_net.h>


int client_instance_rx_icmp(eth_hdr_t *ethhdr, ipv4_hdr_t *iphdr, uint16_t ip_len);


#endif /* __CLIENT_INSTANCE_RX_ICMP_H__ */
