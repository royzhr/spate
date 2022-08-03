/*
 * Rodzhang
 *
 */

#include "dpdk_percpu_module.h"
#include "dpdk_percpu_mgr.h"
#include "dpdk_percpu_cfg_ops.h"


static int _dpdk_percpu_module_init(void)
{
    if (dpdk_percpu_mgr_init() < 0) {
        return -1;
    }

    return 0;
}

static int _dpdk_percpu_module_setting(void)
{
    if (dpdk_percpu_mgr_setting() < 0) {
        return -1;
    }

    return 0;
}

static void _dpdk_percpu_module_exit(void)
{

    dpdk_percpu_mgr_exit();
}

const module_class_t c_dpdk_percpu_module = {
    .module_name    = "dpdk_percpu",
    .cfg_ops        = &c_dpdk_percpu_cfg_ops, 
    .module_init    = _dpdk_percpu_module_init,
    .module_setting = _dpdk_percpu_module_setting,
    .module_exit    = _dpdk_percpu_module_exit,
};


