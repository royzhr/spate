/*
 *  Rodzhang
 *
 * The comm used of client&server
 */

#ifndef __EBPF_CONFIG_COMM_H__
#define __EBPF_CONFIG_COMM_H__


#include "spate_config_struct.h"


typedef struct {

    int                     icmp_enable;
    int                     arp_enable;

    spate_cfg_ipv4_t        host_ip;

} spate_ebpf_host_config_t;

typedef struct {

    int                     ifindex;
    uint8_t                 mac_addr[6];

} spate_ebpf_net_device_config_t;


#endif /* __EBPF_CONFIG_COMM_H__ */
