/*
 * Rodzhang
 *
 */

#ifndef __SERVER_INSTANCE_RX_PAYLOAD_H__
#define __SERVER_INSTANCE_RX_PAYLOAD_H__


#include <spate_core.h>
#include <spate_payload.h>
#include <spate_plane.h>


static inline int __server_instance_rx_payload(spate_payload_t *ps, uint16_t len)
{
    if (unlikely(len < sizeof(*ps))) {
        return INSTANCE_RX_RET_DROP;
    }

    if (unlikely(!__spate_payload_is_magic_right(ps))) {
        return INSTANCE_RX_RET_DROP;
    }

    return INSTANCE_RX_RET_TX;
}



#endif /* __SERVER_INSTANCE_RX_PAYLOAD_H__ */
