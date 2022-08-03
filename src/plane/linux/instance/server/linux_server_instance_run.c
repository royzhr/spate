#include "linux_server_instance.h"
#include "linux_server_instance_run.h"
#include "linux_server_instance_loop.h"
#include <spate_utils.h>


void linux_server_instance_run(instance_context_t *ins_ctx)
{
    server_instance_context_t         *ctx;

    ctx = container_of(ins_ctx, server_instance_context_t, base);

    linux_server_instance_loop(ctx);
}


