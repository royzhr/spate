/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_CLIENT_CFG_METHOD_H__
#define __EBPF_CLIENT_CFG_METHOD_H__


#include "ebpf_client_cfg.h"

int  ebpf_offload_component_client_cfg_constructor(ebpf_offload_component_client_cfg_t *imp, 
        const ebpf_offload_cfg_t *cfg);
void ebpf_offload_component_client_cfg_destructor(ebpf_offload_component_client_cfg_t *imp);



#endif /* __EBPF_CLIENT_CFG_METHOD_H__ */
