/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SERVER_METHOD_H__
#define __EBPF_SERVER_METHOD_H__



#include "ebpf_server_imp.h"

int  ebpf_offload_mode_server_constructor(ebpf_offload_mode_server_t *imp, 
        const ebpf_offload_cfg_t *cfg);
void ebpf_offload_mode_server_destructor(ebpf_offload_mode_server_t *imp);



#endif /* __EBPF_SERVER_METHOD_H__ */
