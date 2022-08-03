/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_CLIENT_RX_ARP_H__
#define __EBPF_SPATE_CLIENT_RX_ARP_H__


#include "ebpf_spate_client_dep.h"



static __inline int __ebpf_spate_client_rx_arp(arp_hdr_t *arp, uint16_t len, 
        spate_ebpf_client_config_t *cfg)
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
    
#ifdef SPATE_EBPF_DEBUG
    char            fmt4[] = "spate client replay arp";
    bpf_trace_printk(fmt4, sizeof(fmt4));
#endif

    return XDP_TX;

}



#endif /* __EBPF_SPATE_CLIENT_RX_ARP_H__ */
