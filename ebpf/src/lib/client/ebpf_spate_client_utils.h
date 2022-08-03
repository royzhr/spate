/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_CLIENT_UTILS_H__
#define __EBPF_SPATE_CLIENT_UTILS_H__


#include "ebpf_spate_client_dep.h"


static __inline int __ebpf_is_client_sip(spate_ebpf_client_config_t *cfg, uint32_t ip)
{
    return __spate_cfg_ip_is_contain(&cfg->session.sip, ip);
}

static __inline int __ebpf_is_client_sport(spate_ebpf_client_config_t *cfg, uint16_t port)
{
    return __spate_cfg_port_is_contain(&cfg->session.sport, port);
}

static __inline int __ebpf_is_client_vxlan_packet(spate_ebpf_client_config_t *cfg, 
        spate_vxlan_underlay_info_t *ui)
{
    if(!__spate_cfg_ip_is_contain(&cfg->vxlan.underlay_sip, ui->underlay_dip)) {
        return 0;
    }

    if(!__spate_cfg_ip_is_contain(&cfg->vxlan.underlay_dip, ui->underlay_sip)) {
        return 0;
    }

    return 1;
}


#endif /* __EBPF_SPATE_CLIENT_UTILS_H__ */

