/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include "linux_netdev_mgr.h"
#include "device/linux_netdev_factory.h"
#include "../../plane.h"



int  linux_netdev_mgr_init(void)
{
    linux_netdev_mgr_t       *mgr;

    mgr = mm_vmalloc(sizeof(*mgr));
    if (!mgr) {
        return -1;
    }

    memset(mgr, 0, sizeof(*mgr));

    __set_linux_netdev_mgr(mgr);

    return 0;
}

int  linux_netdev_mgr_setting(void)
{
    linux_netdev_mgr_t       *mgr;

    mgr = __get_linux_netdev_mgr();

    g_plane->netdev = linux_netdev_factory(&mgr->_export.cfg);
    if (!g_plane->netdev) {
        LOGE("linux netdev create error");
        return -1;
    }

    return 0;
}

void linux_netdev_mgr_exit(void)
{
    linux_netdev_mgr_t       *mgr;

    mgr = __get_linux_netdev_mgr();

    if (g_plane->netdev) {
        g_plane->netdev->vptr->destroy(g_plane->netdev);
        g_plane->netdev = NULL;
    }

    mm_vfree(mgr, sizeof(*mgr));

    __set_linux_netdev_mgr(NULL);
}

