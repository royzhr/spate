/*
 * Rodzhang
 *
 */

#ifndef __HOST_CFG_H__
#define __HOST_CFG_H__


#include <spate_core.h>
#include <spate_config.h>
#include <spate_module.h>

/*
 * Host moudle config block
 */
typedef struct {

    spate_cfg_ipv4_t        host_ip;

    int                     arp_enable;
    int                     icmp_enable;

    int                     garp_enable;
    int                     garp_vlan_enable;
    uint16_t                garp_vlan_id;

} host_cfg_t;





#endif /* __HOST_CFG_H__ */


