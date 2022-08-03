/*
 *  Rodzhang
 *
 */

#include "http_module.h"
#include "http_cfg_ops.h"
#include "http_mgr.h"



static int _http_module_init(void)
{
    if (http_mgr_init() < 0) {
        return -1;
    }

    return 0;
}

static int _http_module_setting(void)
{
    if (http_mgr_setting() < 0) {
        return -1;
    }

    return 0;
}

static void _http_module_exit(void)
{
    http_mgr_exit();
}

const module_class_t c_http_module = {
    .module_name    = "http",
    .cfg_ops        = &c_http_cfg_ops,
    .module_init    = _http_module_init,
    .module_setting = _http_module_setting,
    .module_exit    = _http_module_exit,
};
