/*
 * Rodzhang
 *
 */

#ifndef __SERVER_INSTANCE_CONTEXT_METHOD_H__
#define __SERVER_INSTANCE_CONTEXT_METHOD_H__


#include "server_instance_context.h"


int  server_instance_context_constructor(server_instance_context_t *ctx, uint16_t worker_id);
void server_instance_context_destructor(server_instance_context_t *ctx);


#endif /* __SERVER_INSTANCE_CONTEXT_METHOD_H__ */
