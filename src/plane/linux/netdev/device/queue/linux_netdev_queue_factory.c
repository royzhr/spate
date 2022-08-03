/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include "linux_netdev_queue_factory.h"
#include "linux_netdev_queue_method.h"


plane_linux_netdev_queue_t *linux_netdev_queue_factory(plane_linux_netdev_t *netdev,
        linux_netdev_cfg_t *cfg, uint16_t queue_id)
{
    linux_netdev_queue_t        *queue;

    queue = mm_vmalloc(sizeof(*queue));
    if (!queue) {
        return NULL;
    }
    
    if (linux_netdev_queue_constructor(queue, netdev, cfg, queue_id) < 0) {
        mm_vfree(queue, sizeof(*queue));
        return NULL;
    }

    return &queue->base;
}
