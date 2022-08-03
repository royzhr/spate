/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_OFFLOAD_MODE_H__
#define __EBPF_OFFLOAD_MODE_H__


#include <spate_core.h>
#include "../ebpf_offload_cfg.h"

struct _ebpf_offload_mode_s;

typedef struct {

    int (*attach)(struct _ebpf_offload_mode_s *my);
    int (*detach)(struct _ebpf_offload_mode_s *my);

    void (*destroy)(struct _ebpf_offload_mode_s *my);

} ebpf_offload_mode_vtbl_t;


typedef struct _ebpf_offload_mode_s {
    
    const ebpf_offload_mode_vtbl_t    *vptr;

} ebpf_offload_mode_t;

ebpf_offload_mode_t *ebpf_offload_mode_create(const ebpf_offload_cfg_t *cfg);


#endif /* __EBPF_OFFLOAD_MODE_H__ */

