/*
 * Rodzhang
 *
 */


#include "fack_tcp_module.h"
#include "fack_tcp_mgr.h"
#include "fack_tcp_cfg_ops.h"


static int _fack_tcp_module_init(void)
{
    if (fack_tcp_mgr_init() < 0) {
        return -1;
    }

    return 0;
}

static int _fack_tcp_module_setting(void)
{

    if (fack_tcp_mgr_setting() < 0) {
        return -1;
    }

    return 0;
}

static void _fack_tcp_module_exit(void)
{

    fack_tcp_mgr_exit();
}

const module_class_t c_fack_tcp_module = {
    .module_name    = "client_fack_tcp",
    .cfg_ops        = &c_fack_tcp_cfg_ops,
    .module_init    = _fack_tcp_module_init,
    .module_setting = _fack_tcp_module_setting,
    .module_exit    = _fack_tcp_module_exit,
};


