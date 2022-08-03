/*
 * Rodzhang
 *
 * the config parsing & loading of DEV module
 */

#ifndef __LINUX_NETDEV_CFG_H__
#define __LINUX_NETDEV_CFG_H__

#include <stdint.h>

typedef struct {
    
    char        *name;

    /*
     * must be power of 2
     */
    uint16_t    rx_desc, tx_desc;

    int         is_bypass_qdisc;

} linux_netdev_cfg_t;



#endif /* __LINUX_NETDEV_CFG_H__ */
