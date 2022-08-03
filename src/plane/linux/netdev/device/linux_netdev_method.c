/*
 * Rodzhang
 *
 */

#include "linux_netdev_method.h"
#include "linux_netdev_info.h"
#include "linux_netdev_queues.h"


int  linux_netdev_constructor(plane_linux_netdev_t *netdev, linux_netdev_cfg_t *cfg)
{
    memset(netdev, 0, sizeof(*netdev));

    if (linux_netdev_info_get(netdev, cfg) < 0) {
        return -1;
    }

    if (linux_netdev_queues_constructor(netdev, cfg) < 0) {
        return -1;
    }
    
    return 0;
}

void linux_netdev_destructor(plane_linux_netdev_t *netdev)
{
    linux_netdev_queues_destructor(netdev);

    linux_netdev_info_put(netdev);
}


