/*
 * Rodzhang
 *
 */

#ifndef __CLIENT_INSTANCE_RX_VXLAN_H__
#define __CLIENT_INSTANCE_RX_VXLAN_H__



#include "client_instance_rx_ip.h"


int client_instance_rx_vxlan(eth_hdr_t *ethhdr, char *ip, 
        uint16_t len, client_instance_rx_param_t *rxp);


#endif /* __CLIENT_INSTANCE_RX_VXLAN_H__ */
