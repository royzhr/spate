/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_debug.h>
#include "dpdk_netdev_info.h"
#include "dpdk_netdev_vtbl.h"
#include "dpdk_netdev_ftbl.h"
#include "../../dpdk_inc.h"

int dpdk_netdev_info_get(plane_dpdk_netdev_t *netdev)
{
    struct rte_ether_addr       ethaddr;
    uint16_t                    port_id;
    char                        str[128];

    port_id = netdev->port_id;

    rte_eth_macaddr_get(port_id, &ethaddr);

    memcpy(netdev->base.info.mac_addr, ethaddr.addr_bytes, NP_ETH_ALEN);
    
    __mac_addr_to_string(netdev->base.info.mac_addr, str, 128);

    netdev->fptr      = &c_dpdk_netdev_ftbl;
    netdev->base.vptr = &c_dpdk_netdev_base_vtbl;

    LOGW("my mac addr: %s", str);

    return 0;
}


void dpdk_netdev_info_put(plane_dpdk_netdev_t *netdev)
{
    netdev->fptr      = NULL;
    netdev->base.vptr = NULL;
}

