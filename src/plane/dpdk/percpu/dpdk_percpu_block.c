/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include <spate_main.h>
#include "../plane_dpdk_utils.h"
#include "../../plane_utils.h"
#include "dpdk_percpu_block.h"
#include "dpdk_percpu_mgr.h"



static inline int __dpdk_percpu_blocks_alloc(dpdk_percpu_mgr_t *mgr, uint16_t nr)
{
    mgr->blocks = mm_vmalloc(sizeof(dpdk_percpu_block_t)*nr);
    if (!mgr->blocks) {
        return -1;
    }

    memset(mgr->blocks, 0, sizeof(dpdk_percpu_block_t)*nr);

    mgr->blocks_nr = nr;
    return 0;
}

static inline void __dpdk_percpu_blocks_free(dpdk_percpu_mgr_t *mgr)
{
    if (mgr->blocks) {
        mm_vfree(mgr->blocks, sizeof(dpdk_percpu_block_t)*mgr->blocks_nr);
        mgr->blocks = NULL;
    }
}

static inline uint32_t __dpdk_percpu_mbuf_pool_size(dpdk_percpu_mgr_t *mgr)
{
    uint32_t            n, t;
    uint32_t            desc;
    plane_dpdk_t        *dpdk;

    if (mgr->_export.cfg.mbuf_pool_size) {
        return mgr->_export.cfg.mbuf_pool_size;
    }

    dpdk = __get_plane_dpdk();

    desc = dpdk->netdev->cfg.rx_desc + dpdk->netdev->cfg.tx_desc;
    
    t = desc + SPATE_MAX_BURST + 2*SPATE_MEMPOOL_CACHE_SIZE;

    n = RTE_MAX(t, 8192U);

    return n;
}

static int _dpdk_percpu_block_build(dpdk_percpu_block_t *block, uint32_t n, uint16_t id)
{
    char                name[128];

    sprintf(name, "mbuf_pool_%u", id);

    /*
     * TODO: according lcore to chose socket_id for NUMA adaptation.
     */
    block->mbuf_pool = rte_pktmbuf_pool_create(name, n, SPATE_MEMPOOL_CACHE_SIZE,
            0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());

    if (!block->mbuf_pool) {
        return -1;
    }

    block->id = id;

    return 0;
}


int  dpdk_percpu_block_init(void)
{
    return 0;
}

int  dpdk_percpu_block_setting(void)
{
    dpdk_percpu_mgr_t       *mgr;
    dpdk_percpu_block_t     *block;
    uint16_t                cpu_nr, i;
    uint32_t                n;
    
    mgr = __get_dpdk_percpu_mgr();

    cpu_nr = __plane_get_worker_nr();

    if (__dpdk_percpu_blocks_alloc(mgr, cpu_nr) < 0) {
        return -1;
    }

    n = __dpdk_percpu_mbuf_pool_size(mgr);

    for (i=0; i<cpu_nr; ++i) {
        block = &mgr->blocks[i];

        if (_dpdk_percpu_block_build(block, n, i) < 0) {
            return -1;
        }
    }

    return 0;
}

void dpdk_percpu_block_exit(void)
{
    __dpdk_percpu_blocks_free(__get_dpdk_percpu_mgr());
}

