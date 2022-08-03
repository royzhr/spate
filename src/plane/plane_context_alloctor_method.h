/*
 * Rodzhang
 *
 */

#ifndef __PLANE_CONTEXT_ALLOCTOR_METHOD_H__
#define __PLANE_CONTEXT_ALLOCTOR_METHOD_H__


#include "plane_context_alloctor.h"

int  plane_context_alloctor_constructor(plane_context_alloctor_t *alloctor,
        const plane_context_alloctor_vtbl_t *vtbl);
void plane_context_alloctor_destructor(plane_context_alloctor_t *alloctor);




#endif /* __PLANE_CONTEXT_ALLOCTOR_METHOD_H__ */
