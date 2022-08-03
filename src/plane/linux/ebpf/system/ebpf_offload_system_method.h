/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_OFFLOAD_SYSTEM_METHOD_H__
#define __EBPF_OFFLOAD_SYSTEM_METHOD_H__


#include "ebpf_offload_system_imp.h"

int ebpf_offload_system_constructor(ebpf_offload_system_imp_t *imp, const ebpf_offload_cfg_t *cfg);
void ebpf_offload_system_destructor(ebpf_offload_system_imp_t *imp);



#endif /* __EBPF_OFFLOAD_SYSTEM_METHOD_H__ */
