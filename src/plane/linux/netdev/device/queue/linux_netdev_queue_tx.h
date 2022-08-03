/*
 * Rodzhang
 *
 */

#ifndef __LINUX_NETDEV_QUEUE_TX_H__
#define __LINUX_NETDEV_QUEUE_TX_H__


#include "linux_netdev_queue.h"


uint16_t linux_netdev_queue_tx_get_idle(plane_linux_netdev_queue_t *my,
        char **bufs, uint16_t *lens, uint16_t buf_nr);


uint16_t linux_netdev_queue_tx_xmit(plane_linux_netdev_queue_t *my,
        char **bufs, uint16_t *lens, uint16_t buf_nr);

void linux_netdev_queue_tx_flush(plane_linux_netdev_queue_t *my, 
        uint16_t *lens, uint16_t nr);


#endif /* __LINUX_NETDEV_QUEUE_TX_H__ */
