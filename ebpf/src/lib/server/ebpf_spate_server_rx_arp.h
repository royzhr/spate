/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_SERVER_RX_ARP_H__
#define __EBPF_SPATE_SERVER_RX_ARP_H__


#include "ebpf_spate_server_dep.h"



static __inline int __ebpf_spate_server_rx_arp(arp_hdr_t *arp, uint16_t len, 
        spate_ebpf_server_config_t *cfg)
{
    if (!cfg->host.arp_enable) {
        return XDP_PASS;
    }
    
    if (!__spate_is_arphdr_check_ok(arp, len)) {
        return XDP_PASS;
    }

    
    if (!__ebpf_host_is_my_ip(&cfg->host, arp->arp_data.arp_tip)) {
        return XDP_PASS;
    }
    
    __spate_arphdr_modify_to_replay(arp, cfg->device.mac_addr);
    
    return XDP_TX;

}


#endif /* __EBPF_SPATE_SERVER_RX_ARP_H__ */
