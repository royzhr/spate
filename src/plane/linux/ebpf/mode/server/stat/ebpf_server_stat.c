/*
 *  Rodzhang
 *
 */


#include <spate_mm.h>
#include "ebpf_server_stat.h"
#include "ebpf_server_stat_vtbl.h"
#include "ebpf_server_stat_method.h"


ebpf_offload_component_t *ebpf_offload_component_server_stat_create(const ebpf_offload_cfg_t *cfg)
{
    ebpf_offload_component_server_stat_t         *c;

    c = mm_vmalloc(sizeof(*c));
    if (!c) {
        return NULL;
    }

    if (ebpf_offload_component_server_stat_constructor(c, cfg) < 0) {
        mm_vfree(c, sizeof(*c));
        return NULL;
    }

    return &c->base;
}




