/*
 * Rodzhang
 *
 */

#include "plane_instance_method.h"

int  plane_instance_constructor(plane_instance_t *ins, const plane_instance_vtbl_t *vtbl)
{
    ins->vptr = vtbl;
    return 0;
}

void plane_instance_destructor(plane_instance_t *ins)
{
    ins->vptr = NULL;
}

