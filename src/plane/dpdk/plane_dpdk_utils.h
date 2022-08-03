/*
 * Rodzhang
 *
 */

#ifndef __PLANE_DPDK_UTILS_H__
#define __PLANE_DPDK_UTILS_H__

#include "plane_dpdk.h"
#include "plane_dpdk_netdev.h"
#include <spate_utils.h>


static inline plane_dpdk_t *__get_plane_dpdk(void)
{
    return container_of(g_plane, plane_dpdk_t, base);
}


static inline plane_dpdk_netdev_t *__get_plane_dpdk_netdev(void)
{
    return container_of(g_plane->netdev, plane_dpdk_netdev_t, base);
}




#endif /* __PLANE_DPDK_UTILS_H__ */
