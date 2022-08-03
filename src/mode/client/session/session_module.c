/*
 * Rodzhang
 *
 */

#include "session_module.h"
#include "session_mgr.h"
#include "session_cfg_ops.h"


static int _session_module_init(void)
{
    if (session_mgr_init() < 0) {
        return -1;
    }

    return 0;
}

static int _session_module_setting(void)
{

    if (session_mgr_setting() < 0) {
        return -1;
    }

    return 0;
}

static void _session_module_exit(void)
{

    session_mgr_exit();
}

const module_class_t c_session_module = {
    .module_name    = "client_session",
    .cfg_ops        = &c_session_cfg_ops,
    .module_init    = _session_module_init,
    .module_setting = _session_module_setting,
    .module_exit    = _session_module_exit,
};


