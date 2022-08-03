/*
 * Rodzhang
 *
 */

#ifndef __LINUX_NETDEV_QUEUE_METHOD_H__
#define __LINUX_NETDEV_QUEUE_METHOD_H__


#include "linux_netdev_queue.h"


int  linux_netdev_queue_constructor(linux_netdev_queue_t *queue, 
        plane_linux_netdev_t *netdev, linux_netdev_cfg_t *cfg, uint16_t queue_id);

void linux_netdev_queue_destructor(linux_netdev_queue_t *queue);



#endif /* __LINUX_NETDEV_QUEUE_METHOD_H__ */
