/*
 * Rodzhang
 *
 */

#ifndef __PLANE_LINUX_UTILS_H__
#define __PLANE_LINUX_UTILS_H__

#include "plane_linux.h"
#include "plane_linux_netdev.h"
#include <spate_utils.h>


static inline plane_linux_t *__get_plane_linux(void)
{
    return container_of(g_plane, plane_linux_t, base);
}

static inline linux_filter_t *__get_plane_linux_filter(void)
{
    return __get_plane_linux()->filter;
}

static inline plane_linux_netdev_t *__get_plane_linux_netdev(void)
{
    return container_of(g_plane->netdev, plane_linux_netdev_t, base);
}


static inline plane_linux_netdev_queue_t *__get_plane_linux_netdev_queue(uint16_t queue_id)
{
    plane_linux_netdev_t        *netdev;
    plane_linux_netdev_queue_t  *queue;

    netdev = __get_plane_linux_netdev();

    ASSERT(queue_id < netdev->queue_nr);

    queue = netdev->queues[queue_id];

    ASSERT(queue->vptr->get_id(queue) == queue_id);

    return queue;
}



#endif /* __PLANE_LINUX_UTILS_H__ */
