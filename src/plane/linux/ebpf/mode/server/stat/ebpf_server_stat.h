/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SERVER_STAT_H__
#define __EBPF_SERVER_STAT_H__


#include "ebpf_server_stat_api.h"
#include <spate_mode_server.h>


typedef struct {

    ebpf_offload_component_t        base;

    /*
     * Private
     */
    int                             map_fd;

    server_stat_info_t              ret_stat;


} ebpf_offload_component_server_stat_t;



#endif /* __EBPF_SERVER_STAT_H__ */
