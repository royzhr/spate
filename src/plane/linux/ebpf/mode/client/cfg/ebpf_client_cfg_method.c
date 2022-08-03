/*
 *  Rodzhang
 *
 */

#include "ebpf_client_cfg_method.h"
#include "ebpf_client_cfg_vtbl.h"
#include "ebpf_client_cfg_build.h"


static int _ebpf_client_open_config_map(const char *mount_path)
{
    char                path[EBPF_MOUNT_PATH_MAX*2];
    int                 fd;

    snprintf(path, sizeof(path), "%s/xdp/globals/spate_client_config", mount_path);

    fd = bpf_obj_get(path);

    LOGW("ebpf client config map: %s fd=%d", path, fd);

    return fd;
}


int  ebpf_offload_component_client_cfg_constructor(ebpf_offload_component_client_cfg_t *imp, 
        const ebpf_offload_cfg_t *cfg)
{
    memset(imp, 0, sizeof(*imp));

    imp->map_fd = _ebpf_client_open_config_map(cfg->mount_path);
    if (imp->map_fd < 0) {
        ebpf_offload_mode_on_map_error();
        return -1;
    }

    if (ebpf_offload_client_config_build(&imp->config) < 0) {
        close(imp->map_fd);
        return -1;
    }

    imp->base.vptr = &c_ebpf_offload_client_cfg_vtbl;

    return 0;
}

void ebpf_offload_component_client_cfg_destructor(ebpf_offload_component_client_cfg_t *imp)
{
    imp->base.vptr = NULL;

    close(imp->map_fd);
}


