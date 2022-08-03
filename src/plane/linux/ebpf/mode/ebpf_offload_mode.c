/*
 *  Rodzhang
 *
 */

#include "ebpf_offload_mode.h"
#include <spate_main.h>
#include "client/ebpf_client.h"
#include "server/ebpf_server.h"


ebpf_offload_mode_t *ebpf_offload_mode_create(const ebpf_offload_cfg_t *cfg)
{
    if (g_cmdline->mode == SPATE_MODE_CLIENT) {
        return ebpf_offload_mode_client_create(cfg);

    } else if (g_cmdline->mode == SPATE_MODE_SERVER) {
        return ebpf_offload_mode_server_create(cfg);
    }

    return NULL;
}


