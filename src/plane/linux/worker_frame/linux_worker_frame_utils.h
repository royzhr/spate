/*
 * Rodzhang
 *
 */

#ifndef __LINUX_WORKER_FRAME_UTILS_H__
#define __LINUX_WORKER_FRAME_UTILS_H__


#include "linux_worker_frame.h"
#include "../../plane_utils.h"
#include <spate_utils.h>


static inline plane_linux_worker_frame_t *__get_linux_worker_frame(void)
{
    return container_of(g_plane->worker_frame, plane_linux_worker_frame_t, base);
}

static inline linux_worker_frame_cfg_t *__get_linux_worker_frame_cfg()
{
    plane_linux_worker_frame_t      *wf;

    wf = __get_linux_worker_frame();

    return &wf->cfg;
}


#endif /* __LINUX_WORKER_FRAME_UTILS_H__ */
