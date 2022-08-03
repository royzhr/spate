/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SERVER_PROTOCOL_CFG_H__
#define __EBPF_SERVER_PROTOCOL_CFG_H__


#include <stdint.h>
#include <linux/bpf.h>

#include "../config/ebpf_config_comm.h"

typedef struct {
    
    spate_cfg_ipv4_t        listen_ip;

    spate_cfg_port_t        listen_port;

    uint32_t                proto_tcp : 1,
                            proto_udp : 1,
                            reserved  : 30;

} spate_server_listen_t;


typedef struct {

    int                     vxlan_enable;

    spate_cfg_ipv4_t        vtep_ip;

} spate_server_vxlan_t;




typedef struct {

    int                             enable;

    spate_server_listen_t           listen;

    spate_server_vxlan_t            vxlan;

    spate_ebpf_host_config_t        host;

    spate_ebpf_net_device_config_t  device;

} spate_ebpf_server_config_t;


#endif /* __EBPF_SERVER_PROTOCOL_CFG_H__ */
