/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include "dpdk_context_factory.h"
#include "dpdk_context_method.h"


plane_context_t *dpdk_context_factory(uint16_t worker_id)
{
    plane_dpdk_context_t    *ctx;

    ctx = mm_vmalloc(sizeof(*ctx));

    if (!ctx) {
        return NULL;
    }

    if (dpdk_context_constructor(ctx, worker_id) < 0) {
        mm_vfree(ctx, sizeof(*ctx));
        return NULL;
    }

    return &ctx->base;
}
