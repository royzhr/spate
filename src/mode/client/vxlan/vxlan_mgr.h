/*
 * Rodzhang
 *
 */

#ifndef __VXLAN_MGR_H__
#define __VXLAN_MGR_H__


#include "vxlan_export.h"
#include <spate_session.h>

typedef struct {

    vxlan_export_t      _export;

    /*
     * Private:
     */

    /*
     * From the perspective of the source or dest, 
     * How many overlay ips are there on each underlay ip.
     */
    uint16_t            overlay_per_underlay_on_source;
    uint16_t            overlay_per_underlay_on_dest;

} vxlan_mgr_t;


int  vxlan_mgr_init(void);
int  vxlan_mgr_setting(void);
void vxlan_mgr_exit(void);

extern vxlan_mgr_t *s_vxlan_mgr;

static inline vxlan_cfg_t *__vxlan_cfg_block_get(void)
{
    return &g_vxlan->cfg;
}



#endif /* __VXLAN_MGR_H__ */
