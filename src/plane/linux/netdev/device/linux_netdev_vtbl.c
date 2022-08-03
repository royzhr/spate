/*
 * Rodzhang
 *
 */

#include "linux_netdev_vtbl.h"
#include "linux_netdev_method.h"
#include "../../plane_linux_utils.h"
#include <spate_mm.h>
#include <spate_utils.h>

static void _linux_netdev_destroy(plane_netdev_t *my)
{
    plane_linux_netdev_t        *netdev;

    netdev = container_of(my, plane_linux_netdev_t, base);

    linux_netdev_destructor(netdev);

    mm_vfree(netdev, sizeof(*netdev));
}

static inline void __linux_netdev_copy_pkts(char **bufs, char **pkts, 
        uint16_t *lens, uint16_t nr)
{
    uint16_t                    i;

    for (i=0; i<nr; ++i) {
        memcpy(bufs[i], pkts[i], lens[i]);
    }
}

static uint16_t _linux_netdev_tx_packets(plane_netdev_t *my, char **pkts, 
        uint16_t *lens, uint16_t pkt_nr, uint16_t worker_id)
{
    plane_linux_netdev_queue_t  *queue;
    char                        *bufs[pkt_nr];
    uint16_t                    queue_id;
    uint16_t                    idle_nr, tx_nr;

    ASSERT(my == g_plane->netdev);

    queue_id = worker_id;

    queue = __get_plane_linux_netdev_queue(queue_id);

    idle_nr = queue->vptr->tx_get_idle(queue, bufs, NULL, pkt_nr);

    __linux_netdev_copy_pkts(bufs, pkts, lens, idle_nr);

    tx_nr = queue->vptr->tx_xmit(queue, bufs, lens, idle_nr);

    if (tx_nr) {
        queue->vptr->tx_flush(queue, lens, tx_nr);
    }

    return tx_nr;
}

const plane_netdev_vtbl_t c_linux_netdev_base_vtbl = {
    .tx_packets = _linux_netdev_tx_packets,
    .destroy    = _linux_netdev_destroy,
};


