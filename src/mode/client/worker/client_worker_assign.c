/*
 * Rodzhang
 *
 * assign job to workers
 */

#include <spate_core.h>
#include "client_worker_mgr.h"
#include "client_worker_assign.h"
#include "instance/client_instance_context_method.h"
#include "../session/session.h"


int  client_worker_assign_init(void)
{
    return 0;
}

int  client_worker_assign_setting(void)
{
    uint16_t                    worker_nr, i;
    client_instance_context_t   *ctx;

    worker_nr = s_client_worker_mgr->worker_nr;

    for (i=0; i<worker_nr; ++i) {
        ctx = &s_client_worker_mgr->contexts[i];

        if (client_instance_context_constructor(ctx, i, worker_nr) < 0) {
            return -1;
        }
    }

    return 0;
}

void client_worker_assign_exit(void)
{
    uint16_t                    worker_nr, i;
    client_instance_context_t   *ctx;

    worker_nr = s_client_worker_mgr->worker_nr;

    for (i=0; i<worker_nr; ++i) {
        ctx = &s_client_worker_mgr->contexts[i];

        client_instance_context_destructor(ctx);
    }
}

