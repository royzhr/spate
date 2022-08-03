/*
 * Rodzhang
 *
 */

#include "instance_context.h"
#include <spate_plane.h>
#include <spate_todo.h>
#include <spate_main.h>

/*
 * TLS (per thread) 
 */
__thread instance_context_t *g_instance_ctx = NULL;


int  instance_context_constructor(instance_context_t *ctx, uint16_t worker_id)
{
    ctx->is_master = worker_id==0 ? 1 : 0;

    ctx->worker_id = worker_id;

    ctx->plane_ctx = g_plane->context_alloctor->vptr->alloc_context(g_plane->context_alloctor, 
            worker_id);
    if (!ctx->plane_ctx) {
        return -1;
    }

    if (g_main->pcap_enable) {
        ctx->pcap_file = g_pcap->ops->file_create(worker_id);
    }

    return 0;
}

void instance_context_destructor(instance_context_t *ctx)
{
    if (ctx->pcap_file) {
        ctx->pcap_file->vptr->destroy(ctx->pcap_file);
        ctx->pcap_file = NULL;
    }

    if (ctx->plane_ctx) {
        ctx->plane_ctx->vptr->destroy(ctx->plane_ctx);
        ctx->plane_ctx = NULL;
    }

}

