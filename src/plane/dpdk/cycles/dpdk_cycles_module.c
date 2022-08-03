/*
 * Rodzhang
 *
 */

#include "dpdk_cycles_module.h"
#include "dpdk_cycles_factory.h"
#include "../../plane_utils.h"



static int  _dpdk_cycles_module_init(void)
{
    __plane_cycles_clean();

    g_plane->cycles = plane_dpdk_cycles_factory();
    if (!g_plane->cycles) {
        return -1;
    }

    return 0;
}

static int  _dpdk_cycles_module_setting(void)
{

    return 0;
}

static void _dpdk_cycles_module_exit(void)
{
    __plane_cycles_clean();
}

const module_class_t c_dpdk_cycles_module = {
    .module_name    = "dpdk_cycles",
    .cfg_ops        = NULL,
    .module_init    = _dpdk_cycles_module_init,
    .module_setting = _dpdk_cycles_module_setting,
    .module_exit    = _dpdk_cycles_module_exit,
};
