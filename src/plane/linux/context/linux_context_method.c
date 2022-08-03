/*
 * Rodzhang
 *
 */

#include "linux_context_method.h"
#include "linux_context_vtbl.h"
#include "../plane_linux_utils.h"
#include "../../plane_context_method.h"


int  linux_context_constructor(plane_linux_context_t *ctx, __UNUSED__ uint16_t worker_id)
{
    memset(ctx, 0, sizeof(*ctx));

    if (plane_context_constructor(&ctx->base, &c_linux_context_vtbl) < 0) {
        return -1;
    }

    return 0;
}

void linux_context_destructor(plane_linux_context_t *ctx)
{

    plane_context_destructor(&ctx->base);
}



