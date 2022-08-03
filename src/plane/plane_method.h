/*
 * Rodzhang
 *
 */

#ifndef __PLANE_METHOD_H__
#define __PLANE_METHOD_H__

#include "plane.h"


int  plane_constructor(plane_t *plane, const plane_vtbl_t *vtbl, 
        const plane_param_table_t *params, 
        const module_class_t *module_class);
void plane_destructor(plane_t *plane);




#endif /* __PLANE_METHOD_H__ */
