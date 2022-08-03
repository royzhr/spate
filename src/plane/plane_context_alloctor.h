/*
 * Rodzhang
 *
 */

#ifndef __PLANE_CONTEXT_ALLOCTOR_H__
#define __PLANE_CONTEXT_ALLOCTOR_H__

#include "plane_context.h"

struct _plane_context_alloctor_s;

typedef struct {

    plane_context_t *(*alloc_context)(struct _plane_context_alloctor_s *my, uint16_t worker_id);
    void (*destroy)(struct _plane_context_alloctor_s *my);

} plane_context_alloctor_vtbl_t;


typedef struct _plane_context_alloctor_s {
    
    const plane_context_alloctor_vtbl_t *vptr;

} plane_context_alloctor_t;

#endif /* __PLANE_CONTEXT_ALLOCTOR_H__ */
