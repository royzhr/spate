/*
 * Rodzhang
 *
 */

#include "server_worker_module.h"
#include "server_worker_mgr.h"


static int _server_worker_module_init(void)
{
    if (server_worker_mgr_init() < 0) {
        return -1;
    }

    return 0;
}

static int _server_worker_module_setting(void)
{
    if (server_worker_mgr_setting() < 0) {
        return -1;
    }

    return 0;
}

static void _server_worker_module_exit(void)
{

    server_worker_mgr_exit();
}

const module_class_t c_server_worker_module = {
    .module_name    = "server_worker",
    .cfg_ops        = NULL,
    .module_init    = _server_worker_module_init,
    .module_setting = _server_worker_module_setting,
    .module_exit    = _server_worker_module_exit,
};

