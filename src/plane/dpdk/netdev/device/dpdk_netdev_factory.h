/*
 * Rodzhang
 *
 */

#ifndef __DPDK_NETDEV_FACTORY_H__
#define __DPDK_NETDEV_FACTORY_H__


#include "../../plane_dpdk_netdev.h"
#include "../dpdk_netdev_cfg.h"


plane_netdev_t *dpdk_netdev_factory(dpdk_netdev_cfg_t *cfg);


#endif /* __DPDK_NETDEV_FACTORY_H__ */
