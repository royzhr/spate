/*
 * Rodzhang
 *
 */

#include "linux_context_vtbl.h"
#include "linux_context_method.h"
#include <spate_mm.h>
#include <spate_utils.h>


static void _linux_context_destroy(plane_context_t *my)
{
    plane_linux_context_t        *ctx;

    ctx = container_of(my, plane_linux_context_t, base);

    linux_context_destructor(ctx);

    mm_vfree(ctx, sizeof(*ctx));
}

const plane_context_vtbl_t c_linux_context_vtbl = {
    .destroy = _linux_context_destroy,
};


