/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_SERVER_RX_PAYLOAD_H__
#define __EBPF_SPATE_SERVER_RX_PAYLOAD_H__


#include "ebpf_spate_server_dep.h"

static __inline int __ebpf_spate_server_rx_payload(spate_payload_t *ps, uint16_t len)
{
    if (unlikely(len < sizeof(*ps))) {
        return XDP_PASS;
    }

    if (unlikely(!__spate_payload_is_magic_right(ps))) {
        return XDP_PASS;
    }

    return XDP_TX;
}


#endif /* __EBPF_SPATE_SERVER_RX_PAYLOAD_H__ */
