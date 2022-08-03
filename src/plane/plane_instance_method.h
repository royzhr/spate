/*
 * Rodzhang
 *
 */

#ifndef __PLANE_INSTANCE_METHOD_H__
#define __PLANE_INSTANCE_METHOD_H__


#include "plane_instance.h"

int  plane_instance_constructor(plane_instance_t *ins, const plane_instance_vtbl_t *vtbl);
void plane_instance_destructor(plane_instance_t *ins);


#endif /* __PLANE_INSTANCE_METHOD_H__ */
