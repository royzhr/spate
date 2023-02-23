/*
 *  Rodzhang
 *
 */

#include "ebpf_offload_module.h"
#include "ebpf_offload_mgr.h"
#include "ebpf_offload_cfg_ops.h"



static int  _ebpf_offload_module_init(void)
{
    if (ebpf_offload_mgr_init() < 0) {
        return -1;
    }

    return 0;
}

static int  _ebpf_offload_module_setting(void)
{
    if (!s_ebpf_offload_mgr->cfg.offload_enable) {
        return 0;
    }

    if (ebpf_offload_mgr_setting() < 0) {
        return -1;
    }


    return 0;
}

static void _ebpf_offload_module_exit(void)
{

    ebpf_offload_mgr_exit();
}

const module_class_t c_ebpf_offload_module = {
    .module_name    = "ebpf_offload",
    .cfg_ops        = &c_ebpf_offload_cfg_ops,
    .module_init    = _ebpf_offload_module_init,
    .module_setting = _ebpf_offload_module_setting,
    .module_exit    = _ebpf_offload_module_exit,
};

