/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include "linux_instance_factory.h"
#include "linux_instance_vtbl.h"
#include "../../plane_instance_method.h"


plane_instance_t *plane_linux_instance_factory(void)
{
    plane_instance_t        *ins;

    ins = mm_vmalloc(sizeof(*ins));
    if (!ins) {
        return NULL;
    }

    if (plane_instance_constructor(ins, &c_plane_linux_instance_vtbl) < 0) {
        mm_vfree(ins, sizeof(*ins));
        return NULL;
    }

    return ins;
}


