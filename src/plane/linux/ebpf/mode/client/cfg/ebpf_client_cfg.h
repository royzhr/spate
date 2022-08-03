/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_CLIENT_CFG_H__
#define __EBPF_CLIENT_CFG_H__


#include "ebpf_client_cfg_api.h"


typedef struct {

    ebpf_offload_component_t        base;

    /*
     * Private:
     */
    int                             map_fd;

    spate_ebpf_client_config_t      config;

} ebpf_offload_component_client_cfg_t;


#endif /* __EBPF_CLIENT_CFG_H__ */
