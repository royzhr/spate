/*
 *  Rodzhang
 *
 */

#include "ebpf_server_cfg_vtbl.h"
#include "ebpf_server_cfg_build.h"


static int _ebpf_server_open_config_map(const char *mount_path)
{
    char                path[EBPF_MOUNT_PATH_MAX*2];
    int                 fd;

    snprintf(path, sizeof(path), "%s/xdp/globals/spate_server_config", mount_path);

    fd = bpf_obj_get(path);

    LOGW("ebpf server config map: %s fd=%d", path, fd);

    return fd;
}


int  ebpf_offload_component_server_cfg_constructor(ebpf_offload_component_server_cfg_t *imp, 
        const ebpf_offload_cfg_t *cfg)
{
    memset(imp, 0, sizeof(*imp));

    imp->map_fd = _ebpf_server_open_config_map(cfg->mount_path);
    if (imp->map_fd < 0) {
        ebpf_offload_mode_on_map_error();
        return -1;
    }

    if (ebpf_offload_server_config_build(&imp->config) < 0) {
        close(imp->map_fd);
        return -1;
    }

    imp->base.vptr = &c_ebpf_offload_server_cfg_vtbl;

    return 0;
}

void ebpf_offload_component_server_cfg_destructor(ebpf_offload_component_server_cfg_t *imp)
{
    imp->base.vptr = NULL;

    close(imp->map_fd);
}


