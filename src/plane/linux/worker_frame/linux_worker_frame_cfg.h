/*
 * Rodzhang
 *
 */

#ifndef __LINUX_WORKER_FRAME_CFG_H__
#define __LINUX_WORKER_FRAME_CFG_H__


#include <spate_core.h>

typedef struct {

    uint16_t            worker_nr;
    uint16_t            bind_cpu_begin;

    int                 bind_cpu_enable;


} linux_worker_frame_cfg_t;



#endif /* __LINUX_WORKER_FRAME_CFG_H__ */
