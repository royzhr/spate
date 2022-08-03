/*
 * Rodzhang
 *
 */

#ifndef __PLANE_INSTANCE_H__
#define __PLANE_INSTANCE_H__

#include <spate_core.h>
#include <spate_instance.h>


struct _plane_instance_s;

typedef struct {

    void (*instance_run)(struct _plane_instance_s *my, spate_mode_e mode, 
            instance_context_t *ctx);

    void (*destroy)     (struct _plane_instance_s *my);

} plane_instance_vtbl_t;



typedef struct _plane_instance_s {

    const plane_instance_vtbl_t     *vptr;

} plane_instance_t;


#endif /* __PLANE_INSTANCE_H__ */

