/*
 *  Rodzhang
 *
 */

#include "ebpf_server_stat_vtbl.h"
#include "ebpf_server_stat_method.h"
#include "ebpf_server_stat_extend_fn.h"
#include "ebpf_server_stat_map.h"
#include <spate_mm.h>
#include <spate_utils.h>



static int _ebpf_server_stat_attach(ebpf_offload_component_t *my)
{
    ebpf_offload_component_server_stat_t         *imp;

    imp = container_of(my, ebpf_offload_component_server_stat_t, base);

    ebpf_server_stat_map_zero(imp->map_fd);

    g_server_worker->ops->register_server_extend_stat_handler(
            ebpf_server_stat_extend_handler, imp);

    return 0;
}

static int _ebpf_server_stat_detach(ebpf_offload_component_t *my)
{
    ebpf_offload_component_server_stat_t         *imp;

    imp = container_of(my, ebpf_offload_component_server_stat_t, base);

    g_server_worker->ops->unregister_server_extend_stat_handler(
            ebpf_server_stat_extend_handler, imp);

    ebpf_server_stat_map_zero(imp->map_fd);

    return 0;
}

static void _ebpf_server_stat_destroy(ebpf_offload_component_t *my)
{
    ebpf_offload_component_server_stat_t         *imp;

    imp = container_of(my, ebpf_offload_component_server_stat_t, base);

    ebpf_offload_component_server_stat_destructor(imp);

    mm_vfree(imp, sizeof(*imp));
}

const ebpf_offload_component_vtbl_t c_ebpf_offload_server_stat_vtbl = {
    .attach  = _ebpf_server_stat_attach,
    .detach  = _ebpf_server_stat_detach,
    .destroy = _ebpf_server_stat_destroy,
};








