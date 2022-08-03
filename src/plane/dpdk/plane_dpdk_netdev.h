/*
 * Rodzhang
 *
 */

#ifndef __PLANE_DPDK_NETDEV_H__
#define __PLANE_DPDK_NETDEV_H__


#include "../plane_netdev.h"
#include "dpdk_inc.h"

struct _plane_dpdk_netdev_s;

typedef struct {

    uint16_t (*rx_vec)(struct _plane_dpdk_netdev_s *my, uint16_t queue_id, 
            struct rte_mbuf **mbufs, uint16_t mbuf_size);
        
    uint16_t (*tx_vec)(struct _plane_dpdk_netdev_s *my, uint16_t queue_id, 
            struct rte_mbuf **mbufs, uint16_t mbuf_size);

} plane_dpdk_netdev_ftbl_t;



typedef struct _plane_dpdk_netdev_s {

    plane_netdev_t                  base;

    const plane_dpdk_netdev_ftbl_t  *fptr;

    uint16_t                        port_id;
    uint16_t                        queue_nr;

} plane_dpdk_netdev_t;


static inline uint16_t __dpdk_netdev_rx_mbufs(plane_dpdk_netdev_t *netdev,
        uint16_t queue_id, struct rte_mbuf **mbufs, uint16_t mbuf_len)
{
    return netdev->fptr->rx_vec(netdev, queue_id, mbufs, mbuf_len);
}


static inline uint16_t __dpdk_netdev_tx_mbufs(plane_dpdk_netdev_t *netdev, 
        uint16_t queue_id, struct rte_mbuf **mbufs, uint16_t mbuf_len)
{
    uint16_t            idx;
    uint16_t            tx_nr;

    tx_nr = netdev->fptr->tx_vec(netdev, queue_id, mbufs, mbuf_len);

    idx = tx_nr;
    if (unlikely(idx < mbuf_len)) {
        do {
            rte_pktmbuf_free(mbufs[idx++]);
        } while (idx < mbuf_len);
    }

    return tx_nr;
}

static inline uint16_t __dpdk_netdev_tx_mbuf(plane_dpdk_netdev_t *netdev, 
        uint16_t queue_id, struct rte_mbuf *mbuf)
{
    struct rte_mbuf     *mbufs[1];

    mbufs[0] = mbuf;

    return __dpdk_netdev_tx_mbufs(netdev, queue_id, mbufs, 1);
}


#endif /* __PLANE_DPDK_NETDEV_H__ */
