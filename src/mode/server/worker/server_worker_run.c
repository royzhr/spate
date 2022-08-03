/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include "server_worker_run.h"
#include "server_worker_instance.h"



int server_worker_run(void *arg)
{
    int             worker_id;

    worker_id = (int)(long)arg;

    return server_worker_instance(worker_id);
}



