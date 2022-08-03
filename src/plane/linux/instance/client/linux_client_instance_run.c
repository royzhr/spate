/*
 * Rodzhang
 *
 */

#include "linux_client_instance.h"
#include "linux_client_instance_run.h"
#include "linux_client_instance_loop.h"
#include <spate_utils.h>


void linux_client_instance_run(instance_context_t *ins_ctx)
{
    client_instance_context_t       *ctx;

    ctx = container_of(ins_ctx, client_instance_context_t, base);

    linux_client_instance_loop(ctx);
}


