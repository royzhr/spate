/*
 * Rodzhang
 *
 */

#ifndef __SERVER_INSTANCE_RX_IP_H__
#define __SERVER_INSTANCE_RX_IP_H__

#include <spate_core.h>
#include <spate_net.h>
#include <spate_debug.h>
#include <spate_server_listen.h>

#include "server_instance_rx_tcp.h"
#include "server_instance_rx_udp.h"


static inline uint8_t __l4_proto_to_spate(uint8_t proto)
{
    if (proto == IPPROTO_UDP) {
        return SPATE_UDP;
    } else if (proto == IPPROTO_TCP) {
        return SPATE_TCP;
    } else {
        return SPATE_UNKNOW;
    }
}

static inline int __server_instance_rx_ip_listen(ipv4_hdr_t *iphdr, uint16_t len)
{
    uint16_t                l4_len, iphdr_len;
    void                    *l4_hdr;

    if (unlikely(!__is_server_listen_ip(iphdr->dst_addr))) {
        return INSTANCE_RX_RET_DROP;
    }

    iphdr_len = __spate_iphdr_len(iphdr);
    l4_len = len - iphdr_len;
    l4_hdr = (char *)(iphdr) + iphdr_len;

    switch (iphdr->next_proto_id) {
        case IPPROTO_UDP:
            return __server_instance_rx_udp((udp_hdr_t *)(l4_hdr), l4_len);
            break;

        case IPPROTO_TCP:
            return __server_instance_rx_tcp((tcp_hdr_t *)(l4_hdr), l4_len, iphdr);
            break;

        default:
            break;
    }

    return INSTANCE_RX_RET_DROP;
}

int server_instance_rx_ip_other(ipv4_hdr_t *iphdr, uint16_t len);

static inline int __server_instance_rx_ip(ipv4_hdr_t *iphdr, uint16_t len)
{
    int                         ret;
    uint8_t                     spate_proto;

    if (unlikely(!__spate_is_iphdr_check_ok(iphdr, len))) {
        return INSTANCE_RX_RET_DROP;
    }

    spate_proto = __l4_proto_to_spate(iphdr->next_proto_id);

    ret = INSTANCE_RX_RET_DROP;

    if (likely(__is_server_listen_proto(spate_proto))) {

        ret = __server_instance_rx_ip_listen(iphdr, len);

    } else {
        
        ret = server_instance_rx_ip_other(iphdr, len);
    }

    if (ret) {
        __spate_iphdr_reverse_ip(iphdr);
    }

    return ret;
}



#endif /* __SERVER_INSTANCE_RX_IP_H__ */
