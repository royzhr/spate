/*
 * Rodzhang
 *
 */

#include "plane_dpdk_vtbl.h"
#include "plane_dpdk_method.h"
#include <spate_mm.h>
#include <spate_utils.h>
#include "dpdk_inc.h"


static int _plane_dpdk_main_init(__UNUSED__ plane_t *my, int argc, char **argv)
{
    int                 ret;

    ret = rte_eal_init(argc, argv);

    return ret;
}

static void _plane_dpdk_main_exit(__UNUSED__ plane_t *my)
{
}

static void _plane_dpdk_main_destroy(plane_t *my)
{
    plane_dpdk_t        *dpdk;

    dpdk = container_of(my, plane_dpdk_t, base);

    plane_dpdk_destructor(dpdk);

    mm_vfree(dpdk, sizeof(*dpdk));
}

const plane_vtbl_t c_plane_dpdk_vtbl = {
    .main_init = _plane_dpdk_main_init,
    .main_exit = _plane_dpdk_main_exit,
    .destroy   = _plane_dpdk_main_destroy,
};

