/*
 * Rodzhang
 *
 */

#include "plane_method.h"

int  plane_constructor(plane_t *plane, const plane_vtbl_t *vtbl, 
        const plane_param_table_t *params, 
        const module_class_t *module_class)
{
    plane->vptr         = vtbl;
    plane->params       = params;
    plane->module_class = module_class;

    return 0;
}

void plane_destructor(plane_t *plane)
{
    plane->vptr         = NULL;
    plane->params       = NULL;
    plane->module_class = NULL;
}


