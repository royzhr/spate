/*
 * Rodzhang
 *
 */

#ifndef __SERVER_INSTANCE_RX_UDP_H__
#define __SERVER_INSTANCE_RX_UDP_H__


#include <spate_core.h>
#include <spate_net.h>
#include <spate_server_listen.h>
#include "server_instance_rx_payload.h"



static inline int __server_instance_rx_udp(udp_hdr_t *udp, uint16_t len)
{
    spate_payload_t         *ps;
    uint16_t                udphdr_len, payload_len;
    int                     ret;
    
    if (unlikely(!__spate_is_udphdr_check_ok(udp, len))) {
        return INSTANCE_RX_RET_DROP;
    }

    if (unlikely(!__is_server_listen_port(udp->dst_port))) {
        //LOGD("not udp listen port:%u", ntohs(udp->dst_port));
        return INSTANCE_RX_RET_DROP;
    }

    udphdr_len  = sizeof(*udp);
    ps          = (spate_payload_t *)((char *)udp + udphdr_len);

    payload_len = len - udphdr_len;
    
    ret = __server_instance_rx_payload(ps, payload_len);

    if (likely(ret)) {
        __server_udphdr_reverse_port(udp);
    }

    return ret;
}



#endif /* __SERVER_INSTANCE_RX_UDP_H__ */

