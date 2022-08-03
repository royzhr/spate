/*
 * Rodzhang
 *
 */

#include "linux_netdev_queues.h"
#include "queue/linux_netdev_queue_factory.h"


int linux_netdev_queues_constructor(plane_linux_netdev_t *netdev, linux_netdev_cfg_t *cfg)
{
    uint16_t                        i;
    plane_linux_netdev_queue_t      *queue;

    ASSERT(netdev->queue_nr < SPATE_MAX_WORKER);

    for (i=0; i<netdev->queue_nr; ++i) {
        queue = linux_netdev_queue_factory(netdev, cfg, i);

        if (!queue) {
            return -1;
        }

        netdev->queues[i] = queue;
    }
    
    return 0;
}

void linux_netdev_queues_destructor(plane_linux_netdev_t *netdev)
{
    uint16_t                        i;
    plane_linux_netdev_queue_t      *queue;

    ASSERT(netdev->queue_nr < SPATE_MAX_WORKER);

    for (i=0; i<netdev->queue_nr; ++i) {
        queue = netdev->queues[i];

        queue->vptr->destroy(queue);

        netdev->queues[i] = NULL;
    }
}


