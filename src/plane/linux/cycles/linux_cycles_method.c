/*
 * Rodzhang
 *
 */

#include "linux_cycles_method.h"
#include "linux_cycles_vtbl.h"
#include "../../plane_cycles_method.h"
#include <spate_utils.h>


int  plane_linux_cycles_constructor(plane_linux_cycles_t *cycles)
{
    memset(cycles, 0, sizeof(*cycles));

    if (plane_cycles_constructor(&cycles->base, &c_linux_cycles_vtbl)) {
        return -1;
    }

    return 0;
}

void plane_linux_cycles_destructor(plane_linux_cycles_t *cycles)
{

    plane_cycles_destructor(&cycles->base);
}
