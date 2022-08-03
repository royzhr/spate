/*
 * Rodzhang
 *
 */

#ifndef __DPDK_NETDEV_METHOD_H__
#define __DPDK_NETDEV_METHOD_H__


#include "../../plane_dpdk_netdev.h"

int  dpdk_netdev_constructor(plane_dpdk_netdev_t *netdev, uint16_t port_id);
void dpdk_netdev_destructor(plane_dpdk_netdev_t *netdev);


#endif /* __DPDK_NETDEV_METHOD_H__ */
