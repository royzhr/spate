/*
 * Rodzhang
 *
 */

#include "server_listen_module.h"
#include "server_listen_mgr.h"
#include "server_listen_cfg_ops.h"


static int _server_listen_module_init(void)
{
    if (server_listen_mgr_init() < 0) {
        return -1;
    }

    return 0;
}

static int _server_listen_module_setting(void)
{
    if (server_listen_mgr_setting() < 0) {
        return -1;
    }

    return 0;
}

static void _server_listen_module_exit(void)
{

    server_listen_mgr_exit();
}

const module_class_t c_server_listen_module = {
    .module_name    = "server_server_listen",
    .cfg_ops        = &c_server_listen_cfg_ops,
    .module_init    = _server_listen_module_init,
    .module_setting = _server_listen_module_setting,
    .module_exit    = _server_listen_module_exit,
};

