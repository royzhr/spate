/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_plane.h>
#include <spate_host.h>
#include <spate_ctrl.h>
#include "client_worker_instance.h"
#include "client_worker_mgr.h"
#include <spate_utils.h>


static int _client_instance_init(int worker_id)
{
    client_instance_context_t   *ctx;

    ctx = &s_client_worker_mgr->contexts[worker_id];

    g_instance_ctx = &ctx->base;

    MB();

    g_host->ops->on_worker_init(worker_id);

    g_ctrl->sync->vptr->report_on_sync_wait(g_ctrl->sync, worker_id);

    return 0;
}

static void _client_instance_exit(void)
{
    g_instance_ctx = NULL;
}

int client_worker_instance(int worker_id)
{
    if (_client_instance_init(worker_id) < 0) {
        return -1;
    }

    g_plane->instance->vptr->instance_run(g_plane->instance, SPATE_MODE_CLIENT, g_instance_ctx);

    _client_instance_exit();

    return 0;
}


