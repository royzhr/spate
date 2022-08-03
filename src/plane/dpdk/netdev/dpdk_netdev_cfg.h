/*
 * Rodzhang
 *
 * the config parsing & loading of DEV module
 */

#ifndef __DPDK_NETDEV_CFG_H__
#define __DPDK_NETDEV_CFG_H__

#include <stdint.h>

typedef struct {
    
    char        *name;

    /*
     * must be power of 2
     */
    uint16_t    rx_desc, tx_desc;

    int         is_promiscuous;

} dpdk_netdev_cfg_t;



#endif /* __DPDK_NETDEV_CFG_H__ */

