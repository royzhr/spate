/*
 * Rodzhang
 *
 */

#include "dpdk_netdev_method.h"
#include "dpdk_netdev_configure.h"
#include "dpdk_netdev_info.h"
#include "dpdk_netdev_start.h"

int  dpdk_netdev_constructor(plane_dpdk_netdev_t *netdev, uint16_t port_id)
{
    memset(netdev, 0, sizeof(*netdev));

    netdev->port_id = port_id;

    if (dpdk_netdev_configure(netdev) < 0) {
        return -1;
    }

    if (dpdk_netdev_info_get(netdev) < 0) {
        return -1;
    }

    if (dpdk_netdev_start(netdev) < 0) {
        return -1;
    }


    return 0;
}

void dpdk_netdev_destructor(plane_dpdk_netdev_t *netdev)
{
    dpdk_netdev_stop(netdev);

    dpdk_netdev_info_put(netdev);
}


