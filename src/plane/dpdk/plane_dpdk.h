/*
 * Rodzhang
 *
 */

#ifndef __PLANE_DPDK_H__
#define __PLANE_DPDK_H__


#include "../plane.h"
#include "../plane_utils.h"
#include "percpu/dpdk_percpu_export.h"
#include "netdev/dpdk_netdev_export.h"


typedef struct {

    plane_t                 base;
    
    dpdk_percpu_export_t    *percpu;
    dpdk_netdev_export_t    *netdev;

} plane_dpdk_t;



#endif /* __PLANE_DPDK_H__ */
