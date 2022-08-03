/*
 * Rodzhang
 *
 */

#ifndef __LINUX_NETDEV_INFO_H__
#define __LINUX_NETDEV_INFO_H__


#include "linux_netdev.h"

int  linux_netdev_info_get(plane_linux_netdev_t *netdev, linux_netdev_cfg_t *cfg);
void linux_netdev_info_put(plane_linux_netdev_t *netdev);



#endif /* __LINUX_NETDEV_INFO_H__ */
