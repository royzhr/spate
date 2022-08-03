/*
 *  Rodzhang
 *
 */

#include "ebpf_server_method.h"
#include "ebpf_server_vtbl.h"
#include "cfg/ebpf_server_cfg_api.h"
#include "stat/ebpf_server_stat_api.h"


int  ebpf_offload_mode_server_constructor(ebpf_offload_mode_server_t *imp, 
        const ebpf_offload_cfg_t *cfg)
{
    ebpf_offload_component_t        *c, *s;

    memset(imp, 0, sizeof(*imp));

    c = ebpf_offload_component_server_cfg_create(cfg);
    if (!c) {
        return -1;
    }

    s = ebpf_offload_component_server_stat_create(cfg);
    if (!s) {
        c->vptr->destroy(c);
        return -1;
    }

    /*
     * 1st stat, 2nd config.
     */
    imp->components[0] = s;
    imp->components[1] = c;

    imp->base.vptr = &c_ebpf_offload_server_vtbl;

    return 0;
}

void ebpf_offload_mode_server_destructor(ebpf_offload_mode_server_t *imp)
{
    int                             i;
    ebpf_offload_component_t        *component;

    imp->base.vptr = NULL;

    for (i=EBPF_SERVER_COMPONENT_NR-1; i>=0; --i) {
        component = imp->components[i];
        component->vptr->destroy(component);
        imp->components[i] = NULL;
    }
}





