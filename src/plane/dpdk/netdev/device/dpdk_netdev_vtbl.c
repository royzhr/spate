/*
 * Rodzhang
 *
 */

#include "dpdk_netdev_vtbl.h"
#include "dpdk_netdev_method.h"
#include "../../dpdk_inc.h"
#include "../../plane_dpdk_utils.h"
#include <spate_mm.h>
#include <spate_utils.h>


static void _dpdk_netdev_destroy(plane_netdev_t *my)
{
    plane_dpdk_netdev_t     *netdev;

    netdev = container_of(my, plane_dpdk_netdev_t, base);

    dpdk_netdev_destructor(netdev);

    mm_vfree(netdev, sizeof(*netdev));
}

static inline struct rte_mempool *__dpdk_get_worker_rte_mempool(uint16_t worker_id)
{
    return __get_plane_dpdk()->percpu->ops->get_percpu_block(worker_id)->mbuf_pool;
}


static inline int __dpdk_alloc_mbufs(struct rte_mbuf **mbufs, uint16_t nr, uint16_t worker_id)
{
    uint16_t                i;
    struct rte_mempool      *pool;

    for (i=0; i<nr; ++i) {
        mbufs[i] = NULL;
    }

    pool = __dpdk_get_worker_rte_mempool(worker_id);

    for (i=0; i<nr; ++i) {
        mbufs[i] = rte_pktmbuf_alloc(pool);
        if (!mbufs[i]) {
            return -1;
        }
    }

    return 0;
}

static inline void __dpdk_free_mbufs(struct rte_mbuf **mbufs, uint16_t nr, uint16_t worker_id)
{
    uint16_t                i;

    for (i=0; i<nr; ++i) {
        if (mbufs[i]) {
            rte_pktmbuf_free(mbufs[i]);
            mbufs[i] = NULL;
        }
    }

}

static inline void __dpdk_pkts_to_mbufs(struct rte_mbuf **mbufs, 
        char **pkts, uint16_t *lens, uint16_t nr)
{
    uint16_t                i;
    char                    *data;

    for (i=0; i<nr; ++i) {
        data = (char *)mbufs[i]->buf_addr + mbufs[i]->data_off;

        memcpy(data, pkts[i], lens[i]);

        rte_pktmbuf_pkt_len(mbufs[i])  = lens[i];
        rte_pktmbuf_data_len(mbufs[i]) = lens[i];
    }
    
}


static uint16_t _dpdk_netdev_tx_packets(plane_netdev_t *my, char **pkts, 
        uint16_t *lens, uint16_t pkt_nr, uint16_t worker_id)
{ 
    plane_dpdk_netdev_t     *netdev;
    struct rte_mbuf         *mbufs[pkt_nr];

    netdev = container_of(my, plane_dpdk_netdev_t, base);

    if (__dpdk_alloc_mbufs(mbufs, pkt_nr, worker_id) < 0) {
        goto free_mbufs;
    }

    __dpdk_pkts_to_mbufs(mbufs, pkts, lens, pkt_nr);

    return __dpdk_netdev_tx_mbufs(netdev, worker_id, mbufs, pkt_nr);

free_mbufs:
    __dpdk_free_mbufs(mbufs, pkt_nr, worker_id);

    return 0;
}


const plane_netdev_vtbl_t c_dpdk_netdev_base_vtbl = {
    .tx_packets = _dpdk_netdev_tx_packets,
    .destroy    = _dpdk_netdev_destroy,
};

