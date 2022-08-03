/*
 * Rodzhang
 *
 */

#ifndef __CLIENT_INSTANCE_RX_UDP_H__
#define __CLIENT_INSTANCE_RX_UDP_H__


#include <spate_core.h>
#include <spate_net.h>
#include <spate_drop.h>

#include "client_instance_rx_payload.h"



static inline int __client_instance_rx_udp(udp_hdr_t *udp, uint16_t len, 
        client_instance_rx_param_t *rxp)
{
    if (unlikely(!__spate_is_udphdr_check_ok(udp, len))) {
        SPATE_DROP(DROP_UDPHDR_ERROR, udp);
        return INSTANCE_RX_RET_DROP;
    }

    return __client_instance_rx_payload((spate_payload_t *)(udp+1), len-sizeof(*udp), rxp);
}




#endif /* __CLIENT_INSTANCE_RX_UDP_H__ */
