/*
 * Rodzhang
 *
 */

#include "linux_instance_module.h"
#include "linux_instance_factory.h"
#include "../../plane_utils.h"


static int _linux_instance_module_init(void)
{
    __plane_instance_clean();

    g_plane->instance = plane_linux_instance_factory();
    if (!g_plane->instance) {
        return -1;
    }

    return 0;
}

static int _linux_instance_module_setting(void)
{

    return 0;
}

static void _linux_instance_module_exit(void)
{
    __plane_instance_clean();
}

const module_class_t c_linux_instance_module = {
    .module_name    = "linux_instance",
    .cfg_ops        = NULL, 
    .module_init    = _linux_instance_module_init,
    .module_setting = _linux_instance_module_setting,
    .module_exit    = _linux_instance_module_exit,
};


