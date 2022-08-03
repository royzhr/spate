/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include <spate_session.h>
#include "vxlan_mgr.h"
#include "vxlan_ops.h"


vxlan_export_t    *g_vxlan      = NULL;
vxlan_mgr_t       *s_vxlan_mgr  = NULL;


int  vxlan_mgr_init(void)
{
    s_vxlan_mgr = mm_vmalloc(sizeof(*s_vxlan_mgr));

    if (!s_vxlan_mgr) {
        return -1;
    }

    memset(s_vxlan_mgr, 0, sizeof(*s_vxlan_mgr));

    g_vxlan      = &s_vxlan_mgr->_export;
    g_vxlan->ops = &c_vxlan_ops;

    return 0;
}

int  vxlan_mgr_setting(void)
{
    const session_cfg_t     *session_cfg;
    uint16_t                overlay_sip_cnt, underlay_sip_cnt;
    uint16_t                overlay_dip_cnt, underlay_dip_cnt;

    if (!g_vxlan->cfg.enable) {
        return 0;
    }

    session_cfg      = &g_session->cfg;
    overlay_sip_cnt  = session_cfg->sip.cnt;
    underlay_sip_cnt = g_vxlan->cfg.underlay_sip.cnt;
    overlay_dip_cnt  = session_cfg->dip.cnt;
    underlay_dip_cnt = g_vxlan->cfg.underlay_dip.cnt;

    ASSERT(overlay_sip_cnt % underlay_sip_cnt == 0);
    ASSERT(overlay_dip_cnt % underlay_dip_cnt == 0);

    s_vxlan_mgr->overlay_per_underlay_on_source = overlay_sip_cnt / underlay_sip_cnt;
    s_vxlan_mgr->overlay_per_underlay_on_dest   = overlay_dip_cnt / underlay_dip_cnt;

    LOGI("vxlan overlay per underlay: source:%u, dest:%u", 
            s_vxlan_mgr->overlay_per_underlay_on_source,
            s_vxlan_mgr->overlay_per_underlay_on_dest);

    return 0;
}

void vxlan_mgr_exit(void)
{
    mm_vfree(s_vxlan_mgr, sizeof(*s_vxlan_mgr));

    s_vxlan_mgr = NULL;
    g_vxlan     = NULL;
}

