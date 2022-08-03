/*
 * Rodzhang
 *
 */

#ifndef __LINUX_NETDEV_QUEUE_SOCK_H__
#define __LINUX_NETDEV_QUEUE_SOCK_H__


#include "linux_netdev_queue_frame.h"

typedef struct {

    int                 sock_fd;

    char                *map;
    char                *map_rx, *map_tx;

    uint32_t            map_size;
    uint32_t            rx_size, tx_size;

    uint16_t            rx_nr, tx_nr;
    uint16_t            frame_size;

} linux_netdev_queue_sock_t;




#endif /* __LINUX_NETDEV_QUEUE_SOCK_H__ */
