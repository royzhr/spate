/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include "plane_linux.h"
#include "plane_linux_method.h"
#include "../plane_register.h"

static plane_t *_plane_linux_create(void)
{
    plane_linux_t       *lix;

    lix = mm_vmalloc(sizeof(*lix));
    if (!lix) {
        return NULL;
    }

    if (plane_linux_constructor(lix) < 0) {
        mm_vfree(lix, sizeof(*lix));
        return NULL;
    }    

    return &lix->base;
}

const __spate_plane_register__ plane_register_t _c_plane_linux = {
    .name         = "linux",
    .plane_create = _plane_linux_create,
};


