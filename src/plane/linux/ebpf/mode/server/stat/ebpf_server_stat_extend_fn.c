/*
 *  Rodzhang
 *
 */


#include "ebpf_server_stat_extend_fn.h"
#include "ebpf_server_stat_map.h"



const server_stat_info_t *ebpf_server_stat_extend_handler(void *ud)
{
    ebpf_offload_component_server_stat_t    *imp;
    int                                     ret;

    imp = (ebpf_offload_component_server_stat_t *)ud;

    ret = ebpf_server_stat_map_read(imp->map_fd, &imp->ret_stat);

    if (ret < 0) {
        return NULL;
    }

    return &imp->ret_stat;
}




