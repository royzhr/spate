/*
 *  Rodzhang
 *
 */

#include "ebpf_offload_system_method.h"
#include <spate_main.h>
#include "ebpf_offload_system_vtbl.h"
#include "../../plane_linux_utils.h"


int  ebpf_offload_system_constructor(ebpf_offload_system_imp_t *imp, const ebpf_offload_cfg_t *cfg)
{
    char                obj_file_path[EBPF_OFFLOAD_CMD_LENGTH/2];

    memset(imp, 0, sizeof(*imp));

    if (g_cmdline->mode == SPATE_MODE_CLIENT) {
        snprintf(obj_file_path, sizeof(obj_file_path)-1,
                "%s/ebpf_spate_client.o", cfg->obj_path);
        snprintf(imp->cmd_attach, EBPF_OFFLOAD_CMD_LENGTH-1,
                "ip link set %s xdpgeneric obj %s sec xdp_spate_client", 
                 __get_plane_linux()->netdev->cfg.name, obj_file_path);

    } else if (g_cmdline->mode == SPATE_MODE_SERVER) {
        snprintf(obj_file_path, sizeof(obj_file_path)-1,
                "%s/ebpf_spate_server.o", cfg->obj_path);
        snprintf(imp->cmd_attach, EBPF_OFFLOAD_CMD_LENGTH-1,
                "ip link set %s xdpgeneric obj %s sec xdp_spate_server", 
                 __get_plane_linux()->netdev->cfg.name, obj_file_path);

    } else {
        return -1;

    }

    snprintf(imp->cmd_detach, EBPF_OFFLOAD_CMD_LENGTH-1,
            "ip link set dev %s xdpgeneric off", 
            __get_plane_linux()->netdev->cfg.name);

    imp->base.vptr = &c_ebpf_offload_system_vtbl;

    LOGW("attach: %s", imp->cmd_attach);
    LOGW("detach: %s", imp->cmd_detach);

    return 0;
}

void ebpf_offload_system_destructor(ebpf_offload_system_imp_t *imp)
{
    imp->base.vptr = NULL;
}


