/*
 * Rodzhang
 *
 */

#ifndef __LINUX_NETDEV_QUEUES_H__
#define __LINUX_NETDEV_QUEUES_H__


#include "linux_netdev.h"

int  linux_netdev_queues_constructor(plane_linux_netdev_t *netdev, linux_netdev_cfg_t *cfg);
void linux_netdev_queues_destructor(plane_linux_netdev_t *netdev);


#endif /* __LINUX_NETDEV_QUEUES_H__ */
