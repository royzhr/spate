/*
 * Rodzhang
 *
 */


#include "drop_module.h"

static int _drop_module_init(void)
{

    return 0;
}

static int _drop_module_setting(void)
{

    return 0;
}

static void _drop_module_exit(void)
{

}


const module_class_t c_drop_module = {
    .module_name    = "drop",
    .cfg_ops        = NULL,
    .module_init    = _drop_module_init,
    .module_setting = _drop_module_setting,
    .module_exit    = _drop_module_exit,
};
