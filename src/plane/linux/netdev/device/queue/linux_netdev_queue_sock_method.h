/*
 * Rodzhang
 *
 */

#ifndef __LINUX_NETDEV_QUEUE_SOCK_METHOD_H__
#define __LINUX_NETDEV_QUEUE_SOCK_METHOD_H__


#include "linux_netdev_queue_sock.h"


int  linux_netdev_queue_sock_constructor(linux_netdev_queue_sock_t *sock, 
       plane_linux_netdev_t *netdev, linux_netdev_cfg_t *cfg);

void linux_netdev_queue_sock_destructor(linux_netdev_queue_sock_t *sock);



#endif /* __LINUX_NETDEV_QUEUE_SOCK_METHOD_H__ */


