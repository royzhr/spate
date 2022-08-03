/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include "dpdk_worker_frame_factory.h"
#include "dpdk_worker_frame_method.h"


plane_worker_frame_t *plane_dpdk_worker_frame_factory(void)
{
    plane_dpdk_worker_frame_t       *wf;

    wf = mm_vmalloc(sizeof(*wf));
    if (!wf) {
        return NULL;
    }

    if (plane_dpdk_worker_frame_constructor(wf) < 0) {
        mm_vfree(wf, sizeof(*wf));
        return NULL;
    } 

    return &wf->base;
}
