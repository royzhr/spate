/*
 * Rodzhang
 *
 */

#include "linux_worker_frame_vtbl.h"
#include "linux_worker_frame_method.h"
#include "linux_worker_frame_executor.h"
#include <spate_mm.h>
#include <spate_utils.h>



static uint16_t _linux_worker_frame_get_worker_nr(plane_worker_frame_t *my)
{
    plane_linux_worker_frame_t      *wf;

    wf = container_of(my, plane_linux_worker_frame_t, base);

    return wf->cfg.worker_nr;
}

static int _linux_worker_frame_executor_worker(plane_worker_frame_t *my, 
        int (*fn)(void *arg))
{
    plane_linux_worker_frame_t      *wf;

    wf = container_of(my, plane_linux_worker_frame_t, base);

    if (linux_worker_frame_executor(wf, fn) < 0) {
        return -1;
    }

    return 0;
}

static void _linux_worker_frame_executor_wait(plane_worker_frame_t *my)
{
    plane_linux_worker_frame_t      *wf;

    wf = container_of(my, plane_linux_worker_frame_t, base);

    linux_worker_frame_executor_wait(wf);
}

static void _linux_worker_frame_destroy(plane_worker_frame_t *my)
{
    plane_linux_worker_frame_t      *wf;

    wf = container_of(my, plane_linux_worker_frame_t, base);

    plane_linux_worker_frame_destructor(wf);

    mm_vfree(wf, sizeof(*wf));
}


const plane_worker_frame_vtbl_t c_linux_worker_frame_vtbl = {
    .get_worker_nr   = _linux_worker_frame_get_worker_nr,
    .executor_worker = _linux_worker_frame_executor_worker,
    .executor_wait   = _linux_worker_frame_executor_wait,
    .destroy         = _linux_worker_frame_destroy,
}; 

