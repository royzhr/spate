/*
 * Rodzhang
 *
 */

#include "dpdk_context_vtbl.h"
#include "dpdk_context_method.h"
#include <spate_mm.h>
#include <spate_utils.h>


static void _dpdk_context_destroy(plane_context_t *my)
{
    plane_dpdk_context_t        *ctx;

    ctx = container_of(my, plane_dpdk_context_t, base);

    dpdk_context_destructor(ctx);

    mm_vfree(ctx, sizeof(*ctx));
}

const plane_context_vtbl_t c_dpdk_context_vtbl = {
    .destroy = _dpdk_context_destroy,
};


