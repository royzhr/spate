/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include "dpdk_cycles_factory.h"
#include "dpdk_cycles_method.h"


plane_cycles_t *plane_dpdk_cycles_factory(void)
{
    plane_dpdk_cycles_t     *cycles;

    cycles = mm_vmalloc(sizeof(*cycles));
    if (!cycles) {
        return NULL;
    }

    if (plane_dpdk_cycles_constructor(cycles) < 0) {
        mm_vfree(cycles, sizeof(*cycles));
        return NULL;
    }

    return &cycles->base;
}
