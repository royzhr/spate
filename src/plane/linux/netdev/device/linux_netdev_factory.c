/*
 * Rodzhang
 *
 */

#include "linux_netdev_factory.h"
#include "linux_netdev_method.h"
#include <spate_mm.h>


plane_netdev_t *linux_netdev_factory(linux_netdev_cfg_t *cfg)
{
    plane_linux_netdev_t        *netdev;

    netdev = mm_vmalloc(sizeof(*netdev));
    if (!netdev) {
        return NULL;
    }

    if (linux_netdev_constructor(netdev, cfg) < 0) {
        mm_vfree(netdev, sizeof(*netdev));
        return NULL;
    }
    
    return &netdev->base;
}


