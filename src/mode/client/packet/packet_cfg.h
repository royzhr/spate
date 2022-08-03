/*
 * Rodzhang
 *
 */

#ifndef __PACKET_CFG_H__
#define __PACKET_CFG_H__


#include <spate_core.h>
#include <spate_module.h>
#include <spate_net.h>

typedef struct {
    
    uint16_t            payload_size;
    uint16_t            burst_len;

    uint32_t            pps_per_worker;

    
    int                 vlan_enable;
    uint16_t            vlan_id;

    uint8_t             dmac[NP_ETH_ALEN];

} packet_cfg_t;



#endif /* __PACKET_CFG_H__ */


