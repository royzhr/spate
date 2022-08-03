/*
 * Rodzhang
 *
 */

#ifndef __CLIENT_INSTANCE_RX_PAYLOAD_H__
#define __CLIENT_INSTANCE_RX_PAYLOAD_H__


#include <spate_core.h>
#include <spate_main.h>
#include <spate_packet.h>
#include <spate_plane.h>
#include <spate_drop.h>
#include <spate_payload.h>
#include "client_instance_context.h"


static inline int __client_instance_rx_payload(spate_payload_t *ps, uint16_t len, 
        client_instance_rx_param_t *rxp)
{
    uint64_t                tx_cycles, delta;

    if (unlikely(len < sizeof(*ps))) {
        SPATE_DROP(DROP_PAYLOAD_SIZE_ERROR, ps);
        return INSTANCE_RX_RET_DROP;
    }

    if (unlikely(!__spate_payload_is_magic_right(ps))) {
        SPATE_DROP(DROP_PAYLOAD_TAGS_ERROR, ps);
        return INSTANCE_RX_RET_DROP;
    }

    memcpy(&tx_cycles, &ps->tx_cycles, sizeof(uint64_t));

    if (unlikely(rxp->now < tx_cycles)) {
        SPATE_DROP(DROP_PAYLOAD_CYCLES_ERROR, ps);
        return INSTANCE_RX_RET_DROP;
    }

    delta = rxp->now - tx_cycles;

    rxp->need_stat = 1;
    rxp->rx_stat_param.us_latency = __spate_cycles_to_usec(delta);

    return INSTANCE_RX_RET_DROP;
}



#endif /* __CLIENT_INSTANCE_RX_PAYLOAD_H__ */
