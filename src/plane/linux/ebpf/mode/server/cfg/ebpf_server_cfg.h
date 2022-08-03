/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SERVER_CFG_H__
#define __EBPF_SERVER_CFG_H__


#include "ebpf_server_cfg_api.h"


typedef struct {

    ebpf_offload_component_t        base;

    /*
     * Private:
     */
    int                             map_fd;

    spate_ebpf_server_config_t      config;

} ebpf_offload_component_server_cfg_t;



#endif /* __EBPF_SERVER_CFG_H__ */
