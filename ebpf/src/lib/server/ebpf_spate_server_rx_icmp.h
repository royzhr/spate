/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_SERVER_RX_ICMP_H__
#define __EBPF_SPATE_SERVER_RX_ICMP_H__


#include "ebpf_spate_server_dep.h"
#include "ebpf_spate_server_utils.h"


static __inline int __ebpf_spate_server_rx_icmp(icmp_hdr_t *icmp, uint16_t len, ipv4_hdr_t *iph,
        spate_ebpf_server_config_t *cfg)
{

    if (!cfg->host.icmp_enable) {
        return XDP_PASS;
    }

    if (!__ebpf_host_is_my_ip(&cfg->host, iph->dst_addr)) {
        return XDP_PASS;
    }

    if (!__spate_is_icmphdr_check_ok(icmp, len)) {
        return XDP_PASS;
    }

    __spate_icmphdr_modify_to_replay(icmp);

    return XDP_TX;
}

#endif /* __EBPF_SPATE_SERVER_RX_ICMP_H__ */

