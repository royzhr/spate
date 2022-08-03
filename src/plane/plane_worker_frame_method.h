/*
 * Rodzhang
 *
 */

#ifndef __PLANE_WORKER_FRAME_METHOD_H__
#define __PLANE_WORKER_FRAME_METHOD_H__

#include "plane_worker_frame.h"

int  plane_worker_frame_constructor(plane_worker_frame_t *wf, 
        const plane_worker_frame_vtbl_t *vtbl);
void plane_worker_frame_destructor(plane_worker_frame_t *wf);



#endif /* __PLANE_WORKER_FRAME_METHOD_H__ */
