/*
 * Rodzhang
 *
 */

#include "client_worker_module.h"
#include "client_worker_mgr.h"
#include "event/client_worker_event.h"


static int _client_worker_module_init(void)
{
    if (client_worker_mgr_init() < 0) {
        return -1;
    }

    if (client_worker_event_init() < 0) {
        return -1;
    }

    return 0;
}

static int _client_worker_module_setting(void)
{
    if (client_worker_mgr_setting() < 0) {
        return -1;
    }

    if (client_worker_event_setting() < 0) {
        return -1;
    }

    return 0;
}

static void _client_worker_module_exit(void)
{
    client_worker_event_exit();

    client_worker_mgr_exit();
}

const module_class_t c_client_worker_module = {
    .module_name    = "client_worker",
    .cfg_ops        = NULL,
    .module_init    = _client_worker_module_init,
    .module_setting = _client_worker_module_setting,
    .module_exit    = _client_worker_module_exit,
};


