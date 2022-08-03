/*
 * Rodzhang
 *
 */

#include "dpdk_netdev_start.h"
#include "../../dpdk_inc.h"
#include "../../plane_dpdk_utils.h"

int dpdk_netdev_start(plane_dpdk_netdev_t *netdev)
{
    int                 ret;
    uint16_t            port_id;
    plane_dpdk_t        *dpdk;


    port_id = netdev->port_id;

    ret = rte_eth_dev_start(port_id);
    if (ret < 0) {
        LOGE("rte_eth_dev_start error=%d", ret);
    }

    dpdk = __get_plane_dpdk();

    if (dpdk->netdev->cfg.is_promiscuous) {
        rte_eth_promiscuous_enable(port_id);
    } else {
        rte_eth_promiscuous_disable(port_id);
    }

    LOGD("rte_eth_dev_start port=%u", port_id);

    return 0;
}

void dpdk_netdev_stop(plane_dpdk_netdev_t *netdev)
{
    uint16_t            port_id;

    port_id = netdev->port_id;

    rte_eth_dev_stop(port_id);
}


