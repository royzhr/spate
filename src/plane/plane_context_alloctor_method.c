/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include "plane_context_alloctor_method.h"


int  plane_context_alloctor_constructor(plane_context_alloctor_t *alloctor,
        const plane_context_alloctor_vtbl_t *vtbl)
{
    alloctor->vptr = vtbl;

    return 0;
}

void plane_context_alloctor_destructor(plane_context_alloctor_t *alloctor)
{
    alloctor->vptr = NULL;
}

