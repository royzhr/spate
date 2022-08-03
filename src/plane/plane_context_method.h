/*
 * Rodzhang
 *
 */

#ifndef __PLANE_CONTEXT_METHOD_H__
#define __PLANE_CONTEXT_METHOD_H__


#include "plane_context.h"

int  plane_context_constructor(plane_context_t *ctx, const plane_context_vtbl_t *vtbl);
void plane_context_destructor(plane_context_t *ctx);



#endif /* __PLANE_CONTEXT_METHOD_H__ */
