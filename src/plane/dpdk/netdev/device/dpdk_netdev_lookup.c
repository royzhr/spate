/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include "dpdk_netdev_lookup.h"
#include "../../dpdk_inc.h"


int dpdk_netdev_lookup(const char *netdev_name, uint16_t *port_id)
{
    int                         port;
    struct rte_eth_dev_info     info;

    if (!netdev_name) {
        return -1;
    }

    LOGD("availid port count: %u", rte_eth_dev_count_avail());

    RTE_ETH_FOREACH_DEV(port) {

        rte_eth_dev_info_get(port, &info);

        LOGD("portid=%d, name:%s", port, info.device->name);

        if (!strcmp(netdev_name, info.device->name)) {

            LOGD("find  portid = %d", port);

            *port_id = port;
            return 0;
        }

    }

    return -1;
}


