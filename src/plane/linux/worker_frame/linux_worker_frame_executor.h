/*
 * Rodzhang
 *
 */

#ifndef __LINUX_WORKER_FRAME_EXECUTOR_H__
#define __LINUX_WORKER_FRAME_EXECUTOR_H__


#include "linux_worker_frame.h"

int linux_worker_frame_executor(plane_linux_worker_frame_t *wf, 
        int (*fn)(void *arg));

void linux_worker_frame_executor_wait(plane_linux_worker_frame_t *wf);


#endif /* __LINUX_WORKER_FRAME_EXECUTOR_H__ */
