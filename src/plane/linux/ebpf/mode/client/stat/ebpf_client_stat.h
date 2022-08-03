/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_CLIENT_STAT_H__
#define __EBPF_CLIENT_STAT_H__


#include "ebpf_client_stat_api.h"
#include <spate_mode_client.h>


typedef struct {

    ebpf_offload_component_t        base;

    /*
     * Private
     */
    int                             map_fd;

    spate_ebpf_client_stat_t        curr_stat;
    client_stat_info_t              ret_stat;


} ebpf_offload_component_client_stat_t;



#endif /* __EBPF_CLIENT_STAT_H__ */

