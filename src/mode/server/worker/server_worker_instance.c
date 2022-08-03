/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_plane.h>
#include <spate_host.h>
#include <spate_ctrl.h>
#include "server_worker_instance.h"
#include "server_worker_mgr.h"
#include <spate_utils.h>


static int _server_instance_init(int worker_id)
{
    server_instance_context_t   *ctx;

    ctx = &s_server_worker_mgr->contexts[worker_id];

    g_instance_ctx = &ctx->base;

    MB();

    g_host->ops->on_worker_init(worker_id);

    g_ctrl->sync->vptr->report_on_sync_wait(g_ctrl->sync, worker_id);

    return 0;
}

static void _server_instance_exit(void)
{
    g_instance_ctx = NULL;
}


int server_worker_instance(int worker_id)
{
    if (_server_instance_init(worker_id) < 0) {
        return -1;
    }

    g_plane->instance->vptr->instance_run(g_plane->instance, SPATE_MODE_SERVER, g_instance_ctx);

    _server_instance_exit();

    return 0;
}
