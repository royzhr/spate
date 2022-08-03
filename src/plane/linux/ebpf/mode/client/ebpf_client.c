/*
 *  Rodzhang
 *
 */

#include "ebpf_client.h"
#include "ebpf_client_imp.h"
#include "ebpf_client_method.h"
#include <spate_mm.h>



ebpf_offload_mode_t *ebpf_offload_mode_client_create(const ebpf_offload_cfg_t *cfg)
{
    ebpf_offload_mode_client_t      *imp;

    imp = mm_vmalloc(sizeof(*imp));

    if (!imp) {
        return NULL;
    }

    if (ebpf_offload_mode_client_constructor(imp, cfg) < 0) {
        mm_vfree(imp, sizeof(*imp));
        return NULL;
    }

    return &imp->base;
}

