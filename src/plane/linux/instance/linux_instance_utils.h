/*
 * Rodzhang
 *
 */

#ifndef __LINUX_INSTANCE_UTILS_H__
#define __LINUX_INSTANCE_UTILS_H__

#include <stdint.h>
#include "../plane_linux_utils.h"

static inline void __copy_pkts(char **dsts, char **srcs, uint16_t nr)
{
    int                 i;

    for (i=0; i<nr; ++i) {
        dsts[i] = srcs[i];
    }
}

static inline uint16_t __strip_null_pkts(char **pkts, uint16_t *lens, uint16_t len)
{
    uint16_t                u, i;

    for (i=0,u=0; i<len; ++i) {
        if (pkts[i]) {
            if (u != i) {
                pkts[u] = pkts[i];
                lens[u] = lens[i];
            }

            u++;
        }
    }

    return u;
}

static inline uint16_t __linux_queue_tx_pkts(plane_linux_netdev_queue_t *queue, 
        char **pkts, uint16_t *lens, uint16_t pkt_nr)
{
    char                    *tx_pkts[pkt_nr];
    uint16_t                idle_nr, tx_nr;
    uint16_t                i;

    idle_nr = queue->vptr->tx_get_idle(queue, tx_pkts, NULL, pkt_nr);

    for (i=0; i<idle_nr; ++i) {
        memcpy(tx_pkts[i], pkts[i], lens[i]);
    }

    tx_nr = queue->vptr->tx_xmit(queue, tx_pkts, lens, idle_nr);
    ASSERT(tx_nr == idle_nr);

    if (tx_nr) {
        queue->vptr->tx_flush(queue, lens, tx_nr);
    }

    return tx_nr;
}

#endif /* __LINUX_INSTANCE_UTILS_H__ */
