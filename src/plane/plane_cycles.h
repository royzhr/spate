/*
 * Rodzhang
 *
 */

#ifndef __PLANE_CYCLES_H__
#define __PLANE_CYCLES_H__

#include <spate_core.h>


struct _plane_cycles_s;

typedef struct {

    uint64_t (*get_cycles) (struct _plane_cycles_s *my);
    uint64_t (*get_hz)     (struct _plane_cycles_s *my);
    void     (*destroy)    (struct _plane_cycles_s *my);

} plane_cycles_vtbl_t;


typedef struct _plane_cycles_s {
    const plane_cycles_vtbl_t   *vptr;
} plane_cycles_t;



#endif /* __PLANE_CYCLES_H__ */
