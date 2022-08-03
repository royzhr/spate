/*
 * Rodzhang
 *
 */

#include "plane_worker_frame_method.h"


int  plane_worker_frame_constructor(plane_worker_frame_t *wf, 
        const plane_worker_frame_vtbl_t *vtbl)
{
    wf->vptr = vtbl;

    return 0;
}

void plane_worker_frame_destructor(plane_worker_frame_t *wf)
{
    wf->vptr = NULL;
}


