/*
 * Rodzhang
 *
 */

#ifndef __DPDK_WORKER_FRAME_H__
#define __DPDK_WORKER_FRAME_H__

#include <spate_core.h>
#include "../../plane_worker_frame.h"

typedef struct {

    plane_worker_frame_t        base;

    /*
     * The number of workers to start
     */
    uint16_t        worker_nr;

} plane_dpdk_worker_frame_t;



#endif /* __DPDK_WORKER_FRAME_H__ */
