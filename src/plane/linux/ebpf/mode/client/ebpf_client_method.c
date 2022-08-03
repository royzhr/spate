/*
 *  Rodzhang
 *
 */

#include "ebpf_client_method.h"
#include "ebpf_client_vtbl.h"
#include "cfg/ebpf_client_cfg_api.h"
#include "stat/ebpf_client_stat_api.h"


int  ebpf_offload_mode_client_constructor(ebpf_offload_mode_client_t *imp, 
        const ebpf_offload_cfg_t *cfg)
{
    ebpf_offload_component_t        *c, *s;

    memset(imp, 0, sizeof(*imp));

    c = ebpf_offload_component_client_cfg_create(cfg);
    if (!c) {
        return -1;
    }

    s = ebpf_offload_component_client_stat_create(cfg);
    if (!s) {
        c->vptr->destroy(c);
        return -1;
    }

    /*
     * 1st stat, 2nd config.
     */
    imp->components[0] = s;
    imp->components[1] = c;

    imp->base.vptr = &c_ebpf_offload_client_vtbl;

    return 0;
}

void ebpf_offload_mode_client_destructor(ebpf_offload_mode_client_t *imp)
{
    int                             i;
    ebpf_offload_component_t        *component;

    imp->base.vptr = NULL;

    for (i=EBPF_CLIENT_COMPONENT_NR-1; i>=0; --i) {
        component = imp->components[i];
        component->vptr->destroy(component);
        imp->components[i] = NULL;
    }
}

