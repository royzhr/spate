/*
 * Rodzhang
 *
 */

#ifndef __VXLAN_EXPORT_H__
#define __VXLAN_EXPORT_H__


#include <spate_core.h>
#include "vxlan_cfg.h"

typedef struct {

    /*
     * Host order
     */
    uint32_t (*underlay_sip_get)(uint32_t overlay_sip);
    uint32_t (*underlay_dip_get)(uint32_t overlay_dip);

} vxlan_ops_t;


typedef struct {

    const vxlan_ops_t   *ops;
    
    vxlan_cfg_t         cfg;

} vxlan_export_t;


extern vxlan_export_t *g_vxlan;


static inline int __vxlan_is_enable(void)
{
    return g_vxlan->cfg.enable;
}

static inline const uint8_t *__vxlan_underlay_dmac_addr_get(void)
{
    return g_vxlan->cfg.underlay_dmac;
}


#endif /* __VXLAN_EXPORT_H__ */


