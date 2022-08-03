/*
 * Rodzhang
 *
 */


#include "stat_module.h"
#include "stat_mgr.h"
#include "stat_thread.h"
#include "stat_cfg_ops.h"


static int _stat_module_init(void)
{
    if (stat_mgr_init() < 0) {
        return -1;
    }
    
    if (stat_thread_init() < 0) {
        return -1;
    }

    return 0;
}

static int _stat_module_setting(void)
{

    if (stat_mgr_setting() < 0) {
        return -1;
    }

    if (stat_thread_setting() < 0) {
        return -1;
    }

    return 0;
}

static void _stat_module_exit(void)
{
    stat_thread_exit();

    stat_mgr_exit();
}

const module_class_t c_stat_module = {
    .module_name    = "stat",
    .cfg_ops        = &c_stat_cfg_ops,
    .module_init    = _stat_module_init,
    .module_setting = _stat_module_setting,
    .module_exit    = _stat_module_exit,
};


