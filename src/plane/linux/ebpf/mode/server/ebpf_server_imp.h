/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SERVER_IMP_H__
#define __EBPF_SERVER_IMP_H__


#include "ebpf_server.h"
#include "../ebpf_offload_component.h"

#define EBPF_SERVER_COMPONENT_NR    2

typedef struct {

    ebpf_offload_mode_t         base;

    /*
     * Private:
     */
    ebpf_offload_component_t    *components[EBPF_SERVER_COMPONENT_NR];


} ebpf_offload_mode_server_t;



#endif /* __EBPF_SERVER_IMP_H__ */
