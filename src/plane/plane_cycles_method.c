/*
 * Rodzhang
 *
 */

#include "plane_cycles_method.h"


int  plane_cycles_constructor(plane_cycles_t *cycles, const plane_cycles_vtbl_t *vtbl)
{
    cycles->vptr = vtbl;

    return 0;
}

void plane_cycles_destructor(plane_cycles_t *cycles)
{
    cycles->vptr = NULL;
}
