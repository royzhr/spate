/*
 *  Rodzhang
 *
 */

#include <spate_mm.h>
#include "ebpf_client_vtbl.h"
#include "ebpf_client_method.h"
#include <spate_utils.h>


static int _ebpf_offload_mode_client_attach(ebpf_offload_mode_t *my)
{
    int                             i;
    ebpf_offload_mode_client_t      *imp;
    ebpf_offload_component_t        *component;

    imp = container_of(my, ebpf_offload_mode_client_t, base);

    for (i=0; i<EBPF_CLIENT_COMPONENT_NR; ++i) {

        component = imp->components[i];

        if (component->vptr->attach(component) < 0) {
            return -1;
        }
    }

    return 0;
}

static int _ebpf_offload_mode_client_detach(ebpf_offload_mode_t *my)
{
    int                             i;
    ebpf_offload_mode_client_t      *imp;
    ebpf_offload_component_t        *component;

    imp = container_of(my, ebpf_offload_mode_client_t, base);

    for (i=EBPF_CLIENT_COMPONENT_NR-1; i>=0; --i) {

        component = imp->components[i];

        component->vptr->detach(component);
    }

    return 0;
}

static void _ebpf_offload_mode_client_destroy(ebpf_offload_mode_t *my)
{
    ebpf_offload_mode_client_t      *imp;

    imp = container_of(my, ebpf_offload_mode_client_t, base);

    ebpf_offload_mode_client_destructor(imp);

    mm_vfree(imp, sizeof(*imp));
}

const ebpf_offload_mode_vtbl_t c_ebpf_offload_client_vtbl = {
    .attach  = _ebpf_offload_mode_client_attach,
    .detach  = _ebpf_offload_mode_client_detach,
    .destroy = _ebpf_offload_mode_client_destroy,
};

