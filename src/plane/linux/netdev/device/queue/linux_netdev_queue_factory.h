/*
 * Rodzhang
 *
 */

#ifndef __LINUX_NETDEV_QUEUE_FACTORY_H__
#define __LINUX_NETDEV_QUEUE_FACTORY_H__


#include "linux_netdev_queue.h"


plane_linux_netdev_queue_t *linux_netdev_queue_factory(plane_linux_netdev_t *netdev,
        linux_netdev_cfg_t *cfg, uint16_t queue_id);


#endif /* __LINUX_NETDEV_QUEUE_FACTORY_H__ */
