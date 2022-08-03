/*
 * Rodzhang
 *
 */

#include "dpdk_context_method.h"
#include "dpdk_context_vtbl.h"
#include "../plane_dpdk_utils.h"
#include "../../plane_context_method.h"


int  dpdk_context_constructor(plane_dpdk_context_t *ctx, uint16_t worker_id)
{
    plane_dpdk_t            *dpdk;

    memset(ctx, 0, sizeof(*ctx));

    if (plane_context_constructor(&ctx->base, &c_dpdk_context_vtbl) < 0) {
        return -1;
    }

    dpdk = __get_plane_dpdk();

    ctx->percpu_block = dpdk->percpu->ops->get_percpu_block(worker_id);

    ASSERT(ctx->percpu_block->id == worker_id);

    return 0;
}

void dpdk_context_destructor(plane_dpdk_context_t *ctx)
{
    ctx->percpu_block = NULL;

    plane_context_destructor(&ctx->base);
}



