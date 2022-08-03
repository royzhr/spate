/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include "dpdk_cycles_vtbl.h"
#include "dpdk_cycles_method.h"
#include "../dpdk_inc.h"
#include <spate_utils.h>


static uint64_t _dpdk_cycles_get_cycles(__UNUSED__ plane_cycles_t *my)
{
    return rte_get_timer_cycles();
}

static uint64_t _dpdk_cycles_get_hz(plane_cycles_t *my)
{
    plane_dpdk_cycles_t     *cycles;

    cycles = container_of(my, plane_dpdk_cycles_t, base);

    return cycles->cycles_per_second;
}

static void _dpdk_cycles_destroy(plane_cycles_t *my)
{
    plane_dpdk_cycles_t     *cycles;

    cycles = container_of(my, plane_dpdk_cycles_t, base);

    plane_dpdk_cycles_destructor(cycles);
    
    mm_vfree(cycles, sizeof(*cycles));
}

const plane_cycles_vtbl_t c_dpdk_cycles_vtbl = {
    .get_cycles = _dpdk_cycles_get_cycles,
    .get_hz     = _dpdk_cycles_get_hz,
    .destroy    = _dpdk_cycles_destroy,
};

