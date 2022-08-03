/*
 * Rodzhang
 *
 */

#include "dpdk_worker_frame_vtbl.h"
#include "dpdk_worker_frame_method.h"
#include <spate_mm.h>
#include "../dpdk_inc.h"
#include <spate_utils.h>



static uint16_t _dpdk_worker_frame_get_worker_nr(plane_worker_frame_t *my)
{
    plane_dpdk_worker_frame_t   *wf;

    wf = container_of(my, plane_dpdk_worker_frame_t, base);

    return wf->worker_nr;
}

static int _dpdk_worker_frame_executor_worker(__UNUSED__ plane_worker_frame_t *my, 
        int (*fn)(void *arg))
{
    int             id;
    int             lcore_id;

    id = 1;
    RTE_LCORE_FOREACH_WORKER(lcore_id) {

        LOGD("lancnch remote : id:%d, lcore_id:%d", id, lcore_id);

        rte_eal_remote_launch(fn, (void*)(intptr_t)id, lcore_id);

        id++;
    }

    id = 0;
    fn((void*)(intptr_t)id);

    return 0;
}

static void _dpdk_worker_frame_executor_wait(__UNUSED__ plane_worker_frame_t *my)
{
	rte_eal_mp_wait_lcore();
}

static void _dpdk_worker_frame_destroy(plane_worker_frame_t *my)
{
    plane_dpdk_worker_frame_t   *wf;

    wf = container_of(my, plane_dpdk_worker_frame_t, base);

    plane_dpdk_worker_frame_destructor(wf);

    mm_vfree(wf, sizeof(*wf));
}


const plane_worker_frame_vtbl_t c_dpdk_worker_frame_vtbl = {
    .get_worker_nr   = _dpdk_worker_frame_get_worker_nr,
    .executor_worker = _dpdk_worker_frame_executor_worker,
    .executor_wait   = _dpdk_worker_frame_executor_wait,
    .destroy         = _dpdk_worker_frame_destroy,
}; 

