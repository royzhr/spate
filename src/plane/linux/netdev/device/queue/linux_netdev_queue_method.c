/*
 * Rodzhang
 *
 */

#include "linux_netdev_queue_method.h"
#include "linux_netdev_queue_vtbl.h"
#include "linux_netdev_queue_sock_method.h"


static int _linux_netdev_ring_setup(linux_netdev_queue_t *queue)
{
    linux_netdev_ring_t     *ring;

    ring = &queue->rx_ring;
    ring->frames  = (linux_netdev_queue_frame_t *)(queue->sock.map_rx);
    ring->nr      = queue->sock.rx_nr;
    ring->current = 0;

    ring = &queue->tx_ring;
    ring->frames  = (linux_netdev_queue_frame_t *)(queue->sock.map_tx);
    ring->nr      = queue->sock.tx_nr;
    ring->current = 0;

    return 0;
}


int  linux_netdev_queue_constructor(linux_netdev_queue_t *queue, 
        plane_linux_netdev_t *netdev, linux_netdev_cfg_t *cfg, uint16_t queue_id)
{

    memset(queue, 0, sizeof(*queue));

    queue->netdev    = netdev;
    queue->queue_id  = queue_id;

    queue->base.vptr = &c_linux_netdev_queue_vtbl;

    if (linux_netdev_queue_sock_constructor(&queue->sock, netdev, cfg) < 0) {
        return -1;
    }

    if (_linux_netdev_ring_setup(queue) < 0) {
        return -1;
    }

    LOGD("queue %u setup sockfd %d", queue_id, queue->sock.sock_fd);

    return 0;
}

void linux_netdev_queue_destructor(linux_netdev_queue_t *queue)
{

    linux_netdev_queue_sock_destructor(&queue->sock);

    queue->base.vptr = NULL;
}

