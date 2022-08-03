/*
 * Rodzhang
 *
 */

#include "server_instance_context_method.h"
#include "server_instance_ftbl.h"

int  server_instance_context_constructor(server_instance_context_t *ctx, uint16_t worker_id)
{
    if (instance_context_constructor(&ctx->base, worker_id) < 0) {
        return -1;
    }

    ctx->fptr = &c_server_instance_ftbl;

    return 0;
}

void server_instance_context_destructor(server_instance_context_t *ctx)
{
    ctx->fptr = NULL;

    instance_context_destructor(&ctx->base);
}

