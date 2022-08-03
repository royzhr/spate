/*
 * Rodzhang
 *
 */

#include "plane_linux_method.h"
#include "plane_linux_vtbl.h"
#include "plane_linux_params.h"
#include "plane_linux_module_class.h"
#include "../plane_method.h"


int  plane_linux_constructor(plane_linux_t *lix)
{
    memset(lix, 0, sizeof(*lix));

    if (plane_constructor(&lix->base, 
                &c_plane_linux_vtbl,
                &c_plane_linux_params, 
                &c_plane_linux_module) < 0) {
        return -1;
    }

    return 0;
}

void plane_linux_destructor(plane_linux_t *lix)
{

    plane_destructor(&lix->base);
}


