/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SERVER_CFG_METHOD_H__
#define __EBPF_SERVER_CFG_METHOD_H__


#include "ebpf_server_cfg.h"

int  ebpf_offload_component_server_cfg_constructor(ebpf_offload_component_server_cfg_t *imp, 
        const ebpf_offload_cfg_t *cfg);
void ebpf_offload_component_server_cfg_destructor(ebpf_offload_component_server_cfg_t *imp);



#endif /* __EBPF_SERVER_CFG_METHOD_H__ */
