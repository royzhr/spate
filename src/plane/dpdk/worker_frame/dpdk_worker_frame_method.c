/*
 * Rodzhang
 *
 */

#include "dpdk_worker_frame_method.h"
#include "dpdk_worker_frame_vtbl.h"
#include "../../plane_worker_frame_method.h"
#include "../dpdk_inc.h"

static inline uint16_t __dpdk_worker_frame_get_cpu_nr(void)
{
    uint16_t        nr;
    uint32_t        id;

    nr = 1;

	RTE_LCORE_FOREACH_WORKER(id) {
        ++nr;
    }

    return nr;
}


int  plane_dpdk_worker_frame_constructor(plane_dpdk_worker_frame_t *wf)
{
    memset(wf, 0, sizeof(*wf));

    if (plane_worker_frame_constructor(&wf->base, &c_dpdk_worker_frame_vtbl) < 0) {
        return -1;
    }

    wf->worker_nr = __dpdk_worker_frame_get_cpu_nr();

    return 0;
}


void plane_dpdk_worker_frame_destructor(plane_dpdk_worker_frame_t *wf)
{
    wf->worker_nr = 0;

    plane_worker_frame_destructor(&wf->base);
}
