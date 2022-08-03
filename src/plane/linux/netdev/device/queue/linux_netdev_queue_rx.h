/*
 * Rodzhang
 *
 */

#ifndef __LINUX_NETDEV_QUEUE_RX_H__
#define __LINUX_NETDEV_QUEUE_RX_H__


#include "linux_netdev_queue.h"



uint16_t linux_netdev_queue_rx_get_pkts(plane_linux_netdev_queue_t *my,
            char **bufs, uint16_t *lens, uint16_t buf_nr);

uint16_t linux_netdev_queue_rx_clean(plane_linux_netdev_queue_t *my, 
        char **bufs, uint16_t buf_nr);

void linux_netdev_queue_rx_wait(plane_linux_netdev_queue_t *my, 
        uint32_t timeout_us);



#endif /* __LINUX_NETDEV_QUEUE_RX_H__ */
