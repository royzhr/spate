/*
 * Rodzhang
 *
 */

#include "dpdk_client_instance.h"
#include "dpdk_client_instance_run.h"
#include "dpdk_client_instance_loop.h"
#include <spate_utils.h>


void dpdk_client_instance_run(instance_context_t *ins_ctx)
{
    client_instance_context_t       *ctx;

    ctx = container_of(ins_ctx, client_instance_context_t, base);

    dpdk_client_instance_loop(ctx);
}


