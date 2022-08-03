/*
 *  Rodzhang
 *
 */

#include "ebpf_server_cfg_vtbl.h"
#include "ebpf_server_cfg_method.h"
#include <spate_mm.h>
#include <spate_utils.h>



static int _ebpf_server_cfg_attach(ebpf_offload_component_t *my)
{
    ebpf_offload_component_server_cfg_t         *imp;
    uint32_t                                    key;
    int                                         ret;

    imp = container_of(my, ebpf_offload_component_server_cfg_t, base);

    imp->config.enable = 1;

    key = 0;
    ret = bpf_map_update_elem(imp->map_fd, &key, &imp->config, BPF_ANY);

    LOGD("ebpf server attach ret=%d", ret);

    return ret;
}

static int _ebpf_server_cfg_detach(ebpf_offload_component_t *my)
{
    ebpf_offload_component_server_cfg_t         *imp;
    uint32_t                                    key;
    int                                         ret;

    imp = container_of(my, ebpf_offload_component_server_cfg_t, base);

    key = 0;

    imp->config.enable = 0;

    ret = bpf_map_update_elem(imp->map_fd, &key, &imp->config, BPF_ANY);

    //LOGD("ebpf server detach ret=%d", ret);

    return ret;
}

static void _ebpf_server_cfg_destroy(ebpf_offload_component_t *my)
{
    ebpf_offload_component_server_cfg_t         *imp;

    imp = container_of(my, ebpf_offload_component_server_cfg_t, base);

    ebpf_offload_component_server_cfg_destructor(imp);

    mm_vfree(imp, sizeof(*imp));
}

const ebpf_offload_component_vtbl_t c_ebpf_offload_server_cfg_vtbl = {
    .attach  = _ebpf_server_cfg_attach,
    .detach  = _ebpf_server_cfg_detach,
    .destroy = _ebpf_server_cfg_destroy,
};

