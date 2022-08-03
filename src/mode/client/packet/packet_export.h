/*
 * Rodzhang
 *
 */

#ifndef __PACKET_EXPORT_H__
#define __PACKET_EXPORT_H__

#include <spate_core.h>
#include "packet_cfg.h"


typedef struct {
    int (*change_pps_per_worker)(uint32_t pps);
} packet_ops_t;


typedef struct {

    packet_cfg_t        cfg;

    const packet_ops_t  *ops;

} packet_export_t;

extern packet_export_t *g_packet;

static inline const uint8_t *__packet_dmac_addr_get(void)
{
    return g_packet->cfg.dmac;
}

static inline int __packet_is_vlan_enable(void)
{
    return g_packet->cfg.vlan_enable;
}

static inline uint16_t __packet_vlan_id_get(void)
{
    return g_packet->cfg.vlan_id;
}



#endif /* __PACKET_EXPORT_H__ */
