/*
 * Rodzhang
 *
 */

#ifndef __CLIENT_INSTANCE_CONTEXT_METHOD_H__
#define __CLIENT_INSTANCE_CONTEXT_METHOD_H__


#include "client_instance_context.h"


int  client_instance_context_constructor(client_instance_context_t *ctx, 
        uint16_t worker_id, uint16_t worker_nr);

void client_instance_context_destructor(client_instance_context_t *ctx);


#endif /* __CLIENT_INSTANCE_CONTEXT_METHOD_H__ */

