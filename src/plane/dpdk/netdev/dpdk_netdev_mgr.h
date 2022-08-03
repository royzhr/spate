/*
 * Rodzhang
 *
 */

#ifndef __DPDK_NETDEV_MGR_H__
#define __DPDK_NETDEV_MGR_H__


#include "dpdk_netdev_export.h"
#include "../plane_dpdk_utils.h"
#include <spate_utils.h>

typedef struct {
    
    dpdk_netdev_export_t        _export;

    /*
     * Private:
     */


} dpdk_netdev_mgr_t;


int  dpdk_netdev_mgr_init(void);
int  dpdk_netdev_mgr_setting(void);
void dpdk_netdev_mgr_exit(void);


/*
 * Private: Only available at this Module
 */

static inline dpdk_netdev_mgr_t *__get_dpdk_netdev_mgr(void)
{
    plane_dpdk_t            *dpdk;

    dpdk = __get_plane_dpdk();

    return container_of(dpdk->netdev, dpdk_netdev_mgr_t, _export);
}

static inline void __set_dpdk_netdev_mgr(dpdk_netdev_mgr_t *mgr)
{
    plane_dpdk_t            *dpdk;

    dpdk = __get_plane_dpdk();

    dpdk->netdev = &mgr->_export;
}

#endif /* __DPDK_NETDEV_MGR_H__ */
