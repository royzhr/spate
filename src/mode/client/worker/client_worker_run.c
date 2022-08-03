/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include "client_worker_run.h"
#include "client_worker_mgr.h"
#include "client_worker_instance.h"
#include "instance/client_instance_context.h"


int client_worker_run(void *arg)
{
    int             worker_id;

    worker_id = (int)(long)arg;


    return client_worker_instance(worker_id);
}


