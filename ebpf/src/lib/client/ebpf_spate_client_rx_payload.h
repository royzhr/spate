/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_CLIENT_RX_PAYLOAD_H__
#define __EBPF_SPATE_CLIENT_RX_PAYLOAD_H__


#include "ebpf_spate_client_dep.h"
#include "ebpf_spate_client_stat.h"


static __inline int __ebpf_spate_client_rx_payload(spate_payload_t *ps, uint16_t len, 
        spate_ebpf_client_stat_t *stat)
{
    uint64_t                        ns;
    uint64_t                        now;
    uint64_t                        delta;

    if (unlikely(len < sizeof(*ps))) {
        return XDP_PASS;
    }

    if (unlikely(!__spate_payload_is_magic_right(ps))) {
        return XDP_PASS;
    }

#ifdef SPATE_EBPF_DEBUG
    char            fmt4[] = "spate client recv payload ";
    bpf_trace_printk(fmt4, sizeof(fmt4));
#endif

    memcpy(&ns, &ps->tx_cycles, sizeof(uint64_t));

    now = bpf_ktime_get_ns();

    if (now < ns) {
#ifdef SPATE_EBPF_DEBUG
        char            fmt2[] = "spate client recv payload may wrong timestamp";
        bpf_trace_printk(fmt2, sizeof(fmt2));
#endif

        return XDP_DROP;
    }

    delta = now - ns;

    __ebpf_spate_client_stat(stat, delta);

    return XDP_DROP;
}


#endif /* __EBPF_SPATE_CLIENT_RX_PAYLOAD_H__ */
