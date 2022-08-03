/*
 * Rodzhang
 *
 */

#include "plane_dpdk_sub_modules.h"
#include "cycles/dpdk_cycles_module.h"
#include "worker_frame/dpdk_worker_frame_module.h"
#include "context/dpdk_context_module.h"
#include "percpu/dpdk_percpu_module.h"
#include "netdev/dpdk_netdev_module.h"
#include "instance/dpdk_instance_module.h"


/*
 * Plane of DPDK's sub Module Table
 *
 * NOTE:
 * The order of the table is very important.
 */
const module_class_t *c_dpdk_sub_modules[ ] = {
    &c_dpdk_cycles_module,
    &c_dpdk_worker_frame_module,
    &c_dpdk_context_module,
    &c_dpdk_percpu_module,
    &c_dpdk_netdev_module,
    &c_dpdk_instance_module,
    NULL,
};


