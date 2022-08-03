/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include "linux_cycles_vtbl.h"
#include "linux_cycles_method.h"
#include <time.h>
#include <spate_utils.h>


static uint64_t _linux_cycles_get_cycles(__UNUSED__ plane_cycles_t *my)
{
    struct timespec         ts;
    uint64_t                ns;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    ns = ts.tv_nsec + ((uint64_t)ts.tv_sec)*1000UL*1000UL*1000UL;

    return ns;
}

static uint64_t _linux_cycles_get_hz(plane_cycles_t *my)
{
    return 1000UL*1000UL*1000UL;
}

static void _linux_cycles_destroy(plane_cycles_t *my)
{
    plane_linux_cycles_t     *cycles;

    cycles = container_of(my, plane_linux_cycles_t, base);

    plane_linux_cycles_destructor(cycles);
    
    mm_vfree(cycles, sizeof(*cycles));
}

const plane_cycles_vtbl_t c_linux_cycles_vtbl = {
    .get_cycles = _linux_cycles_get_cycles,
    .get_hz     = _linux_cycles_get_hz,
    .destroy    = _linux_cycles_destroy,
};
