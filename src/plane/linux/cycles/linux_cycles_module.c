/*
 * Rodzhang
 *
 */

#include "linux_cycles_module.h"
#include "linux_cycles_factory.h"
#include "../../plane_utils.h"



static int  _linux_cycles_module_init(void)
{
    __plane_cycles_clean();

    g_plane->cycles = plane_linux_cycles_factory();
    if (!g_plane->cycles) {
        return -1;
    }

    return 0;
}

static int  _linux_cycles_module_setting(void)
{

    return 0;
}

static void _linux_cycles_module_exit(void)
{
    __plane_cycles_clean();
}

const module_class_t c_linux_cycles_module = {
    .module_name    = "linux_cycles",
    .cfg_ops        = NULL,
    .module_init    = _linux_cycles_module_init,
    .module_setting = _linux_cycles_module_setting,
    .module_exit    = _linux_cycles_module_exit,
};
