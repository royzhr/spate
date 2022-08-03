/*
 * Rodzhang
 *
 */

#ifndef __PLANE_H__
#define __PLANE_H__

#include <spate_core.h>
#include <spate_module.h>

#include "plane_show.h"
#include "plane_netdev.h"
#include "plane_instance.h"
#include "plane_context_alloctor.h"
#include "plane_worker_frame.h"
#include "plane_cycles.h"


struct _plane_s;

typedef struct {

    int  (*main_init)(struct _plane_s *my, int argc, char **argv);
    void (*main_exit)(struct _plane_s *my);
    
    void (*destroy)(struct _plane_s *my);

} plane_vtbl_t;


typedef struct {
    uint32_t                        startup_wait_msec;
} plane_param_table_t;


/*
 * Plane 
 */
typedef struct _plane_s {
    
    /*
     * Method
     */
    const plane_vtbl_t              *vptr;
    const plane_param_table_t       *params;
    const module_class_t            *module_class;


    /*
     * Public
     */
    plane_instance_t                *instance;
    plane_cycles_t                  *cycles;
    plane_worker_frame_t            *worker_frame;
    plane_context_alloctor_t        *context_alloctor;
    plane_netdev_t                  *netdev;

} plane_t;


int  plane_singleton_add(const char *plane_name);
void plane_singleton_clean(void);


/*
 * plane (singleton) 
 */
extern plane_t *g_plane;




#endif /* __PLANE_H__ */
