/*
 *  Rodzhang
 *
 */

#include "ebpf_offload_system_imp.h"
#include <spate_mm.h>
#include "ebpf_offload_system_method.h"



ebpf_offload_system_t *ebpf_offload_system_create(const ebpf_offload_cfg_t *cfg)
{
    ebpf_offload_system_imp_t       *imp;

    imp = mm_vmalloc(sizeof(*imp));
    if (!imp) {
        return NULL;
    }

    if (ebpf_offload_system_constructor(imp, cfg) < 0) {
        mm_vfree(imp, sizeof(*imp));
        return NULL;
    }

    return &imp->base;
}


