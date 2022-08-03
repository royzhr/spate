/*
 * Rodzhang
 *
 */

#include "vxlan_ops.h"
#include "vxlan_mgr.h"
#include <spate_session.h>

/*
 * Host order 
 */
static inline uint32_t __vxlan_underlay_ip_get(uint32_t oip, uint16_t o_per_u,
        const spate_cfg_ipv4_t *ocfg, const spate_cfg_ipv4_t *ucfg)
{
    uint16_t                od, ud;
    uint32_t                uip;

    ASSERT(__spate_cfg_ip_is_contain_on_host(ocfg, oip));

    od = oip - ocfg->addr;
    ud = od / o_per_u;

    ASSERT(od < ocfg->cnt);
    ASSERT(ud < ucfg->cnt);

    uip = ucfg->addr + ud;

    return uip;
}


static uint32_t _vxlan_underlay_sip_get(uint32_t overlay_sip)
{
    return __vxlan_underlay_ip_get(overlay_sip, s_vxlan_mgr->overlay_per_underlay_on_source, 
            &g_session->cfg.sip, &g_vxlan->cfg.underlay_sip);
}

static uint32_t _vxlan_underlay_dip_get(uint32_t overlay_dip)
{
    return __vxlan_underlay_ip_get(overlay_dip, s_vxlan_mgr->overlay_per_underlay_on_dest, 
            &g_session->cfg.dip, &g_vxlan->cfg.underlay_dip);
}

const vxlan_ops_t c_vxlan_ops = {
    .underlay_sip_get = _vxlan_underlay_sip_get,
    .underlay_dip_get = _vxlan_underlay_dip_get,
};
