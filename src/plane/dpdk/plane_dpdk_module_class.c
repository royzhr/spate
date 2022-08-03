/*
 * Rodzhang
 *
 */

#include "plane_dpdk_module_class.h"
#include "plane_dpdk_cfg_ops.h"
#include "plane_dpdk_sub_modules.h"


static int _plane_dpdk_module_init(void)
{
    if (spate_modules_init(c_dpdk_sub_modules) < 0) {
        LOGE("plane dpdk module init error");
        return -1;
    }

    return 0;
}

static int _plane_dpdk_module_setting(void)
{
    if (spate_modules_setting(c_dpdk_sub_modules) < 0) {
        LOGE("plane dpdk module setting error");
        return -1;
    }
    
    return 0;
}

static void _plane_dpdk_module_exit(void)
{
    spate_modules_exit(c_dpdk_sub_modules);
}

const module_class_t c_plane_dpdk_module = {
    .module_name    = "plane_dpdk",
    .cfg_ops        = &c_plane_dpdk_cfg_ops,
    .module_init    = _plane_dpdk_module_init,
    .module_setting = _plane_dpdk_module_setting,
    .module_exit    = _plane_dpdk_module_exit,
};



