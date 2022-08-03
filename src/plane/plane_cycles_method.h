/*
 * Rodzhang
 *
 */

#ifndef __PLANE_CYCLES_METHOD_H__
#define __PLANE_CYCLES_METHOD_H__


#include "plane_cycles.h"


int  plane_cycles_constructor(plane_cycles_t *cycles, const plane_cycles_vtbl_t *vtbl);
void plane_cycles_destructor(plane_cycles_t *cycles);



#endif /* __PLANE_CYCLES_METHOD_H__ */
