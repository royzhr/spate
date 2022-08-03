/*
 * Rodzhang
 *
 */

#ifndef __LINUX_NETDEV_QUEUE_H__
#define __LINUX_NETDEV_QUEUE_H__


#include "../linux_netdev.h"
#include "linux_netdev_queue_sock.h"
#include "linux_netdev_queue_frame.h"


typedef struct {

    linux_netdev_queue_frame_t      *frames;

    uint16_t                        current;
    uint16_t                        nr;

} linux_netdev_ring_t;

/*
 * Implementation class of plane_linux_netdev_queue_t
 */
typedef struct {

    plane_linux_netdev_queue_t      base;

    plane_linux_netdev_t            *netdev;

    linux_netdev_queue_sock_t       sock;

    uint16_t                        queue_id;


    linux_netdev_ring_t             rx_ring;
    linux_netdev_ring_t             tx_ring;

} linux_netdev_queue_t;



#endif /* __LINUX_NETDEV_QUEUE_H__ */
