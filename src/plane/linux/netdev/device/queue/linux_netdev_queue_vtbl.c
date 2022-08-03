/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include "linux_netdev_queue_vtbl.h"
#include "linux_netdev_queue_method.h"
#include "linux_netdev_queue_rx.h"
#include "linux_netdev_queue_tx.h"
#include <spate_utils.h>


static uint16_t _linux_netdev_queue_get_id(plane_linux_netdev_queue_t *my)
{
    linux_netdev_queue_t        *queue;

    queue = container_of(my, linux_netdev_queue_t, base);

    return queue->queue_id;
}

static void _linux_netdev_queue_destroy(plane_linux_netdev_queue_t *my)
{
    linux_netdev_queue_t        *queue;

    queue = container_of(my, linux_netdev_queue_t, base);

    linux_netdev_queue_destructor(queue);

    mm_vfree(queue, sizeof(queue));
}


const plane_linux_netdev_queue_vtbl_t c_linux_netdev_queue_vtbl = {
    /*
     * Tx
     */
    .tx_get_idle = linux_netdev_queue_tx_get_idle,
    .tx_xmit     = linux_netdev_queue_tx_xmit,
    .tx_flush    = linux_netdev_queue_tx_flush,

    /*
     * Rx
     */
    .rx_get_pkts = linux_netdev_queue_rx_get_pkts,
    .rx_clean    = linux_netdev_queue_rx_clean,
    .rx_wait     = linux_netdev_queue_rx_wait,

    /*
     * Utils
     */
    .get_id      = _linux_netdev_queue_get_id,
    .destroy     = _linux_netdev_queue_destroy,
};
