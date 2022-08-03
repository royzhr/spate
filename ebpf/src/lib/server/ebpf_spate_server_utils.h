/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_SERVER_UTILS_H__
#define __EBPF_SPATE_SERVER_UTILS_H__


#include "ebpf_spate_server_dep.h"

static __inline int __ebpf_is_server_listen_ip(spate_ebpf_server_config_t *cfg, uint32_t ip)
{
    return __spate_cfg_ip_is_contain(&cfg->listen.listen_ip, ip);
}

static __inline int __ebpf_is_server_listen_port(spate_ebpf_server_config_t *cfg, uint16_t port)
{
    return __spate_cfg_port_is_contain(&cfg->listen.listen_port, port);
}

static __inline int __ebpf_is_server_vxlan_packet(spate_ebpf_server_config_t *cfg, 
        spate_vxlan_underlay_info_t *ui)
{
    return __spate_cfg_ip_is_contain(&cfg->vxlan.vtep_ip, ui->underlay_dip);
}


#endif /* __EBPF_SPATE_SERVER_UTILS_H__ */
