/*
 *  Rodzhang
 *
 */

#include "ebpf_server.h"
#include "ebpf_server_imp.h"
#include "ebpf_server_method.h"
#include <spate_mm.h>



ebpf_offload_mode_t *ebpf_offload_mode_server_create(const ebpf_offload_cfg_t *cfg)
{
    ebpf_offload_mode_server_t      *imp;

    imp = mm_vmalloc(sizeof(*imp));

    if (!imp) {
        return NULL;
    }

    if (ebpf_offload_mode_server_constructor(imp, cfg) < 0) {
        mm_vfree(imp, sizeof(*imp));
        return NULL;
    }

    return &imp->base;
}




