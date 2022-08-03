/*
 * Rodzhang
 *
 */

#ifndef __LINUX_CONTEXT_METHOD_H__
#define __LINUX_CONTEXT_METHOD_H__


#include "../plane_linux_context.h"

int  linux_context_constructor(plane_linux_context_t *ctx, uint16_t worker_id);
void linux_context_destructor(plane_linux_context_t *ctx);



#endif /* __LINUX_CONTEXT_METHOD_H__ */
