/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_OFFLOAD_COMPONENT_H__
#define __EBPF_OFFLOAD_COMPONENT_H__


#include <spate_core.h>
#include "ebpf_dep_include.h"
#include "ebpf_offload_mode_utils.h"



struct _ebpf_offload_component_s;

typedef struct {

    int (*attach)(struct _ebpf_offload_component_s *my);
    int (*detach)(struct _ebpf_offload_component_s *my);

    void (*destroy)(struct _ebpf_offload_component_s *my);

} ebpf_offload_component_vtbl_t;


typedef struct _ebpf_offload_component_s {
    
    const ebpf_offload_component_vtbl_t    *vptr;

} ebpf_offload_component_t;


#endif /* __EBPF_OFFLOAD_COMPONENT_H__ */
