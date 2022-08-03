/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_CLIENT_PROTOCOL_CFG_H__
#define __EBPF_CLIENT_PROTOCOL_CFG_H__



#include <stdint.h>
#include <linux/bpf.h>

#include "../config/ebpf_config_comm.h"


typedef struct {

    spate_cfg_ipv4_t        sip;
    spate_cfg_ipv4_t        dip;

    
    spate_cfg_port_t        sport;
    spate_cfg_port_t        dport;

    uint8_t                 proto;

} spate_ebpf_session_config_t;


typedef struct {

    uint16_t                payload_size;
    uint16_t                vlan_enable;
    uint16_t                vlan_id;

    uint8_t                 dmac[6];

} spate_ebpf_packet_config_t;


typedef struct {

    int                     vxlan_enable;

    uint32_t                vni;


    spate_cfg_ipv4_t        underlay_sip;
    spate_cfg_ipv4_t        underlay_dip;
    spate_cfg_port_t        underlay_sport;

    uint8_t                 overlay_smac[6];
    uint8_t                 underlay_dmac[6];

} spate_ebpf_client_vxlan_config_t;


typedef struct {

    int                                 enable;

    spate_ebpf_session_config_t         session;
    spate_ebpf_packet_config_t          packet;
    spate_ebpf_client_vxlan_config_t    vxlan;
    spate_ebpf_host_config_t            host;
    spate_ebpf_net_device_config_t      device;

} spate_ebpf_client_config_t;



#endif /* __EBPF_CLIENT_PROTOCOL_CFG_H__ */
