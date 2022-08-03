/*
 * Rodzhang
 *
 */

#include "dpdk_percpu_ops.h"
#include "dpdk_percpu_mgr.h"

static dpdk_percpu_block_t *_dpdk_percpu_get_block(int id)
{
    dpdk_percpu_block_t     *block;
    dpdk_percpu_mgr_t       *mgr;

    mgr = __get_dpdk_percpu_mgr();

    if (!mgr->blocks) {
        return NULL;
    }
    if (id<0 || id>=mgr->blocks_nr) {
        return NULL;
    }

    block = &mgr->blocks[id];

    ASSERT(block->id == id);

    return block;
}

const dpdk_percpu_ops_t c_dpdk_percpu_ops = {
    .get_percpu_block = _dpdk_percpu_get_block,
};

