/*
 * Rodzhang
 *
 */

#include "plane_context_method.h"



int  plane_context_constructor(plane_context_t *ctx, const plane_context_vtbl_t *vtbl)
{
    ctx->vptr = vtbl;

    return 0;
}

void plane_context_destructor(plane_context_t *ctx)
{
    ctx->vptr = NULL;
}


