/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_CLIENT_IMP_H__
#define __EBPF_CLIENT_IMP_H__


#include "ebpf_client.h"
#include "../ebpf_offload_component.h"

#define EBPF_CLIENT_COMPONENT_NR    2

typedef struct {

    ebpf_offload_mode_t         base;

    /*
     * Private:
     */
    ebpf_offload_component_t    *components[EBPF_CLIENT_COMPONENT_NR];


} ebpf_offload_mode_client_t;


#endif /* __EBPF_CLIENT_IMP_H__ */
