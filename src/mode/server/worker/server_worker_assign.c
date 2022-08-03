/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include "server_worker_assign.h"
#include "server_worker_mgr.h"
#include "instance/server_instance_context.h"
#include "instance/server_instance_context_method.h"



int  server_worker_assign_init(void)
{
    return 0;
}

int  server_worker_assign_setting(void)
{
    uint16_t                    i, worker_nr;
    server_instance_context_t   *ctx;

    worker_nr = s_server_worker_mgr->worker_nr;

    for (i=0; i<worker_nr; ++i) {
        ctx = &s_server_worker_mgr->contexts[i];

        if (server_instance_context_constructor(ctx, i) < 0) {
            return -1;
        }
    }

    return 0;
}

void server_worker_assign_exit(void)
{
    uint16_t                i, worker_nr;
    server_instance_context_t   *ctx;

    worker_nr = s_server_worker_mgr->worker_nr;

    for (i=0; i<worker_nr; ++i) {
        ctx = &s_server_worker_mgr->contexts[i];

        server_instance_context_destructor(ctx);
    }
}
