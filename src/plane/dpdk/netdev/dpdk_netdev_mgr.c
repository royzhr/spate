/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include "dpdk_netdev_mgr.h"
#include "device/dpdk_netdev_factory.h"
#include "../../plane.h"



int  dpdk_netdev_mgr_init(void)
{
    dpdk_netdev_mgr_t       *mgr;

    mgr = mm_vmalloc(sizeof(*mgr));
    if (!mgr) {
        return -1;
    }

    memset(mgr, 0, sizeof(*mgr));

    __set_dpdk_netdev_mgr(mgr);

    return 0;
}

int  dpdk_netdev_mgr_setting(void)
{
    dpdk_netdev_mgr_t       *mgr;

    mgr = __get_dpdk_netdev_mgr();

    g_plane->netdev = dpdk_netdev_factory(&mgr->_export.cfg);
    if (!g_plane->netdev) {
        return -1;
    }

    return 0;
}

void dpdk_netdev_mgr_exit(void)
{
    dpdk_netdev_mgr_t       *mgr;

    mgr = __get_dpdk_netdev_mgr();

    if (g_plane->netdev) {
        g_plane->netdev->vptr->destroy(g_plane->netdev);
        g_plane->netdev = NULL;
    }

    mm_vfree(mgr, sizeof(*mgr));

    __set_dpdk_netdev_mgr(NULL);
}

