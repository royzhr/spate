/*
 * Rodzhang
 *
 */

#include "vxlan_module.h"
#include "vxlan_mgr.h"
#include "vxlan_cfg_ops.h"


static int _vxlan_module_init(void)
{
    if (vxlan_mgr_init() < 0) {
        return -1;
    }

    return 0;
}

static int _vxlan_module_setting(void)
{
    if (vxlan_mgr_setting() < 0) {
        return -1;
    }

    return 0;
}

static void _vxlan_module_exit(void)
{

    vxlan_mgr_exit();
}

const module_class_t c_vxlan_module = {
    .module_name    = "vxlan",
    .cfg_ops        = &c_vxlan_cfg_ops,
    .module_init    = _vxlan_module_init,
    .module_setting = _vxlan_module_setting,
    .module_exit    = _vxlan_module_exit,
};


