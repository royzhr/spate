/*
 * Rodzhang
 *
 */

#include "plane_linux_sub_modules.h"
#include "cycles/linux_cycles_module.h"
#include "worker_frame/linux_worker_frame_module.h"
#include "context/linux_context_module.h"
#include "netdev/linux_netdev_module.h"
#include "instance/linux_instance_module.h"
#include "filter/linux_filter_module.h"

#ifdef EBPF_ENABLE
#include "ebpf/ebpf_offload_module.h"
#endif


/*
 * Plane of DPDK's sub Module Table
 *
 * NOTE:
 * The order of the table is very important.
 */
const module_class_t *c_linux_sub_modules[ ] = {
    &c_linux_cycles_module,
    &c_linux_worker_frame_module,
    &c_linux_context_module,
    &c_linux_filter_module,
    &c_linux_netdev_module,
    &c_linux_instance_module,
#ifdef EBPF_ENABLE
    &c_ebpf_offload_module,
#endif
    NULL,
};


