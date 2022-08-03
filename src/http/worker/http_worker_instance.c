/*
 *  Rodzhang
 *
 */

#include <spate_core.h>
#include "http_worker_instance.h"
#include "http_context.h"
#include "http_recv.h"
#include "http_build_response.h"
#include "http_send.h"

void *http_worker_instance_run(void *args)
{
    int                     fd;
    http_context_t          _ctx;
    http_context_t          *ctx;

    fd = (int)((intptr_t)args);
    ctx = &_ctx;

    http_context_init(ctx, fd);

    if (http_recv_request(ctx) < 0) {
        //LOGW("http not HTTP Protocol");
        goto close_fd_label;
    }

    if (http_build_response(ctx) < 0) {
        goto close_fd_label;
    }

    http_send_response(ctx);

close_fd_label:
    close(ctx->fd);
    return NULL;
}


