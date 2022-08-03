/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include "dpdk_instance_vtbl.h"
#include "../../plane_instance_method.h"
#include "client/dpdk_client_instance_run.h"
#include "server/dpdk_server_instance_run.h"


static void _plane_dpdk_instance_run(__UNUSED__ plane_instance_t *my, 
        spate_mode_e mode, instance_context_t *ctx)
{
    switch (mode) {
        case SPATE_MODE_CLIENT:
            dpdk_client_instance_run(ctx);
            break;

        case SPATE_MODE_SERVER:
            dpdk_server_instance_run(ctx);
            break;

        default:
            ASSERT(0);
            break;
    }
}

static void _plane_dpdk_instance_destroy(plane_instance_t *my)
{
    plane_instance_destructor(my);

    mm_vfree(my, sizeof(*my));
}

const plane_instance_vtbl_t c_plane_dpdk_instance_vtbl = {
    .instance_run = _plane_dpdk_instance_run,
    .destroy      = _plane_dpdk_instance_destroy,
};


