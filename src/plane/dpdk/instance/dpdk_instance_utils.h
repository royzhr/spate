/*
 * Rodzhang
 *
 */

#ifndef __DPDK_INSTANCE_UTILS_H__
#define __DPDK_INSTANCE_UTILS_H__

#include <stdint.h>
#include "../dpdk_inc.h"

static inline uint16_t __strip_null_mbuf(struct rte_mbuf **mbufs, uint16_t len)
{
    uint16_t                u, i;

    for (i=0,u=0; i<len; ++i) {
        if (mbufs[i]) {
            if (u != i) {
                mbufs[u] = mbufs[i];
            }

            u++;
        }
    }

    return u;
}



#endif /* __DPDK_INSTANCE_UTILS_H__ */
