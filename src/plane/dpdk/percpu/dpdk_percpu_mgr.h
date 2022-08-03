/*
 * Rodzhang
 *
 */

#ifndef __DPDK_PERCPU_MGR_H__
#define __DPDK_PERCPU_MGR_H__


#include "dpdk_percpu_export.h"
#include "../plane_dpdk_utils.h"
#include <spate_utils.h>

typedef struct {
    
    dpdk_percpu_export_t   _export;

    /*
     * Private:
     */
    dpdk_percpu_block_t    *blocks;
    uint16_t                blocks_nr;

} dpdk_percpu_mgr_t;


int  dpdk_percpu_mgr_init(void);
int  dpdk_percpu_mgr_setting(void);
void dpdk_percpu_mgr_exit(void);


/*
 * Private: Only available at this Module
 */

static inline dpdk_percpu_mgr_t *__get_dpdk_percpu_mgr(void)
{
    plane_dpdk_t            *dpdk;

    dpdk = __get_plane_dpdk();

    return container_of(dpdk->percpu, dpdk_percpu_mgr_t, _export);
}

static inline void __set_dpdk_percpu_mgr(dpdk_percpu_mgr_t *mgr)
{
    plane_dpdk_t            *dpdk;

    dpdk = __get_plane_dpdk();

    dpdk->percpu = &mgr->_export;
}


#endif /* __DPDK_PERCPU_MGR_H__ */

