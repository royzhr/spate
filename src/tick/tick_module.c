/*
 * Rodzhang
 *
 */

#include "tick_module.h"
#include "tick_mgr.h"
#include "tick_thread.h"


static int _tick_module_init(void)
{
    if (tick_mgr_init() < 0) {
        return -1;
    }

    if (tick_thread_init() < 0) {
        return -1;
    }

    return 0;
}

static int _tick_module_setting(void)
{
    if (tick_mgr_setting() < 0) {
        return -1;
    }
    
    if (tick_thread_setting() < 0) {
        return -1;
    }

    return 0;
}

static void _tick_module_exit(void)
{
    tick_thread_exit();

    tick_mgr_exit();
}

const module_class_t c_tick_module = {
    .module_name    = "tick",
    .cfg_ops        = NULL,
    .module_init    = _tick_module_init,
    .module_setting = _tick_module_setting,
    .module_exit    = _tick_module_exit,
};


