/*
 *  Rodzhang
 *
 */

#include "event_module.h"
#include "event_mgr.h"



static int _event_module_init(void)
{
    if (event_mgr_init() < 0) {
        return -1;
    }

    return 0;
}

static int _event_module_setting(void)
{
    if (event_mgr_setting() < 0) {
        return -1;
    }

    return 0;
}

static void _event_module_exit(void)
{
    event_mgr_exit();
}

const module_class_t c_event_module = {
    .module_name    = "event",
    .cfg_ops        = NULL,
    .module_init    = _event_module_init,
    .module_setting = _event_module_setting,
    .module_exit    = _event_module_exit,
};




