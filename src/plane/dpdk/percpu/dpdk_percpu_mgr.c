/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include "dpdk_percpu.h"
#include "dpdk_percpu_mgr.h"
#include "dpdk_percpu_ops.h"
#include "dpdk_percpu_block.h"



int  dpdk_percpu_mgr_init(void)
{
    dpdk_percpu_mgr_t       *mgr;
    plane_dpdk_t            *dpdk;

    dpdk = __get_plane_dpdk();

    mgr = mm_vmalloc(sizeof(*mgr));
    if (!mgr) {
        return -1;
    }

    memset(mgr, 0, sizeof(*mgr));

    __set_dpdk_percpu_mgr(mgr);
    dpdk->percpu->ops = &c_dpdk_percpu_ops;

    if (dpdk_percpu_block_init() < 0) {
        return -1;
    }

    return 0;
}

int  dpdk_percpu_mgr_setting(void)
{
    if (dpdk_percpu_block_setting() < 0) {
        return -1;
    }

    return 0;
}

void dpdk_percpu_mgr_exit(void)
{
    dpdk_percpu_mgr_t       *mgr;

    mgr = __get_dpdk_percpu_mgr();

    dpdk_percpu_block_exit();

    mm_vfree(mgr, sizeof(*mgr));

    __set_dpdk_percpu_mgr(NULL);
}
