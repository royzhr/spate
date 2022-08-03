/*
 * Rodzhang
 *
 */

#include "dpdk_cycles_method.h"
#include "dpdk_cycles_vtbl.h"
#include "../../plane_cycles_method.h"
#include "../dpdk_inc.h"
#include "tsc_hz.h"
#include <spate_utils.h>


int  plane_dpdk_cycles_constructor(plane_dpdk_cycles_t *cycles)
{
    memset(cycles, 0, sizeof(*cycles));

    if (plane_cycles_constructor(&cycles->base, &c_dpdk_cycles_vtbl)) {
        return -1;
    }

    //cycles->cycles_per_second = rte_get_timer_hz();
    cycles->cycles_per_second = __spate_get_hz();

    LOGW("linux get hz: %lu", cycles->cycles_per_second);

    return 0;
}

void plane_dpdk_cycles_destructor(plane_dpdk_cycles_t *cycles)
{
    cycles->cycles_per_second = 0;

    plane_cycles_destructor(&cycles->base);
}
