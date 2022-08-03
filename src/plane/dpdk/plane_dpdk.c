/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include "plane_dpdk.h"
#include "plane_dpdk_method.h"
#include "../plane_register.h"

static plane_t *_plane_dpdk_create(void)
{
    plane_dpdk_t        *dpdk;

    dpdk = mm_vmalloc(sizeof(*dpdk));
    if (!dpdk) {
        return NULL;
    }

    if (plane_dpdk_constructor(dpdk) < 0) {
        mm_vfree(dpdk, sizeof(*dpdk));
        return NULL;
    }

    return &dpdk->base;
}


const __spate_plane_register__ plane_register_t _c_plane_dpdk = {
    .name         = "dpdk",
    .plane_create = _plane_dpdk_create,
};
