/*
 * Rodzhang
 *
 */

#include "plane_dpdk_method.h"
#include "plane_dpdk_vtbl.h"
#include "plane_dpdk_params.h"
#include "plane_dpdk_module_class.h"
#include "../plane_method.h"


int  plane_dpdk_constructor(plane_dpdk_t *dpdk)
{
    memset(dpdk, 0, sizeof(*dpdk));

    if (plane_constructor(&dpdk->base, 
                &c_plane_dpdk_vtbl, 
                &c_plane_dpdk_params,
                &c_plane_dpdk_module) < 0) {
        return -1;
    }


    return 0;
}

void plane_dpdk_destructor(plane_dpdk_t *dpdk)
{

    plane_destructor(&dpdk->base);
}


