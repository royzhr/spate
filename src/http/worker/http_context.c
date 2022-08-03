/*
 *  Rodzhang
 *
 */

#include "http_context.h"



void http_context_init(http_context_t *ctx, int fd)
{
    memset(ctx, 0, sizeof(*ctx));

    ctx->fd = fd;
}

