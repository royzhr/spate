/*
 * Rodzhang
 *
 */

#include "dpdk_worker_frame_module.h"
#include "dpdk_worker_frame_factory.h"
#include "../../plane_utils.h"


static int  _dpdk_worker_frame_module_init(void)
{
    
    return 0;
}

static int  _dpdk_worker_frame_module_setting(void)
{
    __plane_worker_frame_clean();

    g_plane->worker_frame = plane_dpdk_worker_frame_factory();
    if (!g_plane->worker_frame) {
        return -1;
    }

    return 0;
}

static void _dpdk_worker_frame_module_exit(void)
{
    __plane_worker_frame_clean();
}


const module_class_t c_dpdk_worker_frame_module = {
    .module_name    = "dpdk_worker_frame",
    .cfg_ops        = NULL,
    .module_init    = _dpdk_worker_frame_module_init,
    .module_setting = _dpdk_worker_frame_module_setting,
    .module_exit    = _dpdk_worker_frame_module_exit,
};

