/*
 * Rodzhang
 *
 */

#ifndef __CLIENT_INSTANCE_IP_H__
#define __CLIENT_INSTANCE_IP_H__


#include <spate_core.h>
#include <spate_net.h>
#include <spate_drop.h>

#include "client_instance_rx_tcp.h"
#include "client_instance_rx_udp.h"
#include "client_instance_rx_icmp.h"


static inline int __client_instance_rx_ip(eth_hdr_t *ethhdr, ipv4_hdr_t *iphdr, 
        uint16_t len, client_instance_rx_param_t *rxp)
{
    uint16_t                l4_len, iphdr_len;
    void                    *l4_hdr;

    if (unlikely(!__spate_is_iphdr_check_ok(iphdr, len))) {
        SPATE_DROP(DROP_IPHDR_ERROR, iphdr);
        return INSTANCE_RX_RET_DROP;
    }

    iphdr_len = __spate_iphdr_len(iphdr);
    l4_len = len - iphdr_len;
    l4_hdr = (char *)(iphdr) + iphdr_len;

    if (iphdr->next_proto_id == IPPROTO_UDP) {
    
        return __client_instance_rx_udp((udp_hdr_t *)(l4_hdr), l4_len, rxp);

    } else if (iphdr->next_proto_id == IPPROTO_TCP) {

        return __client_instance_rx_tcp((tcp_hdr_t *)(l4_hdr), l4_len, rxp, iphdr);

    } else if (iphdr->next_proto_id == IPPROTO_ICMP) {
        
        return client_instance_rx_icmp(ethhdr, iphdr, len);
    }

    SPATE_DROP(DROP_IP_PROTO_REJECT, iphdr);
    return INSTANCE_RX_RET_DROP;
}




#endif /* __CLIENT_INSTANCE_IP_H__ */
