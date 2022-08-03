/*
 * Rodzhang
 *
 */

#ifndef __PLANE_WORKER_FRAME_H__
#define __PLANE_WORKER_FRAME_H__

#include <spate_core.h>

struct _plane_worker_frame_s;


typedef struct {


    uint16_t (*get_worker_nr)(struct _plane_worker_frame_s *my);
    int  (*executor_worker)  (struct _plane_worker_frame_s *my, int (*fn)(void *));
    void (*executor_wait)    (struct _plane_worker_frame_s *my);
    void (*destroy)          (struct _plane_worker_frame_s *my);

} plane_worker_frame_vtbl_t;



typedef struct _plane_worker_frame_s {

    const plane_worker_frame_vtbl_t     *vptr;

} plane_worker_frame_t;




#endif /* __PLANE_WORKER_FRAME_H__ */
