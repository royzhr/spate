/*
 * Rodzhang
 *
 */

#include "linux_worker_frame_method.h"
#include "linux_worker_frame_vtbl.h"
#include "../../plane_worker_frame_method.h"



int  plane_linux_worker_frame_constructor(plane_linux_worker_frame_t *wf)
{
    memset(wf, 0, sizeof(*wf));

    if (plane_worker_frame_constructor(&wf->base, &c_linux_worker_frame_vtbl) < 0) {
        return -1;
    }

    return 0;
}


void plane_linux_worker_frame_destructor(plane_linux_worker_frame_t *wf)
{

    plane_worker_frame_destructor(&wf->base);
}

