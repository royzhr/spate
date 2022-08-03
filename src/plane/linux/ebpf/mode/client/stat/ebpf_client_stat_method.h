/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_CLIENT_STAT_METHOD_H__
#define __EBPF_CLIENT_STAT_METHOD_H__



#include "ebpf_client_stat.h"

int  ebpf_offload_component_client_stat_constructor(ebpf_offload_component_client_stat_t *imp, 
        const ebpf_offload_cfg_t *cfg);
void ebpf_offload_component_client_stat_destructor(ebpf_offload_component_client_stat_t *imp);


#endif /* __EBPF_CLIENT_STAT_METHOD_H__ */
