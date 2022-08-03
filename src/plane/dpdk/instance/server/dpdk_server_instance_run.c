/*
 * Rodzhang
 *
 */

#include "dpdk_server_instance.h"
#include "dpdk_server_instance_run.h"
#include "dpdk_server_instance_loop.h"
#include <spate_utils.h>


void dpdk_server_instance_run(instance_context_t *ins_ctx)
{
    server_instance_context_t         *ctx;

    ctx = container_of(ins_ctx, server_instance_context_t, base);

    dpdk_server_instance_loop(ctx);
}




