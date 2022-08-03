/*
 * Rodzhang
 *
 */

#ifndef __DPDK_NETDEV_INFO_H__
#define __DPDK_NETDEV_INFO_H__


#include "../../plane_dpdk_netdev.h"

int  dpdk_netdev_info_get(plane_dpdk_netdev_t *netdev);
void dpdk_netdev_info_put(plane_dpdk_netdev_t *netdev);



#endif /* __DPDK_NETDEV_INFO_H__ */
