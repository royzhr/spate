/*
 * Rodzhang
 *
 */

#ifndef __LINUX_WORKER_FRAME_H__
#define __LINUX_WORKER_FRAME_H__

#include <spate_core.h>
#include "../../plane_worker_frame.h"
#include "linux_worker_frame_cfg.h"
#include <pthread.h>


typedef struct {

    pthread_t       thread;

} linux_worker_thread_t;

typedef struct {

    plane_worker_frame_t        base;

    linux_worker_frame_cfg_t    cfg;

    linux_worker_thread_t       *worker_threads;

} plane_linux_worker_frame_t;





#endif /* __LINUX_WORKER_FRAME_H__ */
