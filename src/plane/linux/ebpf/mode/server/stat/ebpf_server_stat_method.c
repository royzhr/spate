/*
 *  Rodzhang
 *
 */

#include "ebpf_server_stat_method.h"
#include "ebpf_server_stat_vtbl.h"
#include "ebpf_server_stat_map.h"




int  ebpf_offload_component_server_stat_constructor(ebpf_offload_component_server_stat_t *imp, 
        const ebpf_offload_cfg_t *cfg)
{
    memset(imp, 0, sizeof(*imp));

    imp->map_fd = ebpf_server_stat_map_open(cfg->mount_path);
    if (imp->map_fd < 0) {
        ebpf_offload_mode_on_map_error();
        return -1;
    }

    imp->base.vptr = &c_ebpf_offload_server_stat_vtbl;

    return 0;
}

void ebpf_offload_component_server_stat_destructor(ebpf_offload_component_server_stat_t *imp)
{
    imp->base.vptr = NULL;

    ebpf_server_stat_map_close(imp->map_fd);
}



