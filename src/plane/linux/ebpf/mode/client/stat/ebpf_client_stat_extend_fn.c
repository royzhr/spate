/*
 *  Rodzhang
 *
 */

#include "ebpf_client_stat_extend_fn.h"
#include "ebpf_client_stat_map.h"



const client_stat_info_t *ebpf_client_stat_extend_handler(void *ud)
{
    ebpf_offload_component_client_stat_t    *imp;
    int                                     ret;

    imp = (ebpf_offload_component_client_stat_t *)ud;

    ret = ebpf_client_stat_map_read(imp->map_fd, &imp->curr_stat);

    if (ret < 0) {
        return NULL;
    }

    imp->ret_stat.traffic = imp->curr_stat.traffic;
    imp->ret_stat.latency = imp->curr_stat.latency;

    return &imp->ret_stat;
}

