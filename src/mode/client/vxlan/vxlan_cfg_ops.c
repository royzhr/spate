/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_config.h>
#include <spate_session.h>
#include <spate_utils.h>
#include <spate_debug.h>
#include "vxlan_cfg_ops.h"
#include "vxlan_mgr.h"

static inline void __vxlan_cfg_default(vxlan_cfg_t *cfg)
{
    memset(cfg, 0, sizeof(*cfg));

    cfg->enable = 0;
}


static void _vxlan_cfg_begin(void)
{
    vxlan_cfg_t       *cfg;

    cfg = __vxlan_cfg_block_get();

    __vxlan_cfg_default(cfg);
}

/*
 * The count of underlay_sip must be divisible by the count of overlay_sip
 */
static inline int __vxlan_cfg_is_underlay_ip_valid(vxlan_cfg_t *cfg)
{
    const session_cfg_t     *session_cfg;
    uint16_t                overlay_sip_cnt, underlay_sip_cnt;
    uint16_t                overlay_dip_cnt, underlay_dip_cnt;

    session_cfg      = &g_session->cfg;
    overlay_sip_cnt  = session_cfg->sip.cnt;
    underlay_sip_cnt = cfg->underlay_sip.cnt;
    overlay_dip_cnt  = session_cfg->dip.cnt;
    underlay_dip_cnt = cfg->underlay_dip.cnt;

    if (overlay_sip_cnt % underlay_sip_cnt) {
        LOGE("The count of [vxlan.underlay_sip] Must be divisible by the count of [session.sip]");
        return 0;
    }

    if (overlay_dip_cnt % underlay_dip_cnt) {
        LOGE("The count of [vxlan.underlay_dip] Must be divisible by the count of [session.dip]");
        return 0;
    }

    return 1;
}


static int _vxlan_cfg_finish(void)
{
    vxlan_cfg_t       *cfg;

    cfg = __vxlan_cfg_block_get();

    __spate_cfg_ipv4_invalid_to_default(&cfg->underlay_sip);
    __spate_cfg_ipv4_invalid_to_default(&cfg->underlay_dip);

    __spate_cfg_port_invalid_to_default(&cfg->underlay_sport);

    if (!cfg->enable) {
        return 0;
    }

    if (!__vxlan_cfg_is_underlay_ip_valid(cfg)) {
        return -1;
    }

    return 0;
}

static int _vxlan_cfg_parse_line(const char *key, const char *val)
{
    vxlan_cfg_t       *cfg;

    cfg = __vxlan_cfg_block_get();

    if (!strcmp(key, "vxlan.enable")) {
        cfg->enable = __config_parse_bool(val);
        return 1;

    } else if (!strcmp(key, "vxlan.vni")) {
        cfg->vni = __config_parse_uint16(val);
        return 1;

    } else if (!strcmp(key, "vxlan.underlay.dmac")) {
        if (__config_parse_mac_addr(cfg->underlay_dmac, val) < 0) {
            LOGE("config file's [vxlan.underlay.dmac=%s] config error", val);
            return -1;
        }
        return 1;

    } else if (!strcmp(key, "vxlan.underlay.sip")) {
        if (__config_parse_spate_ip(&cfg->underlay_sip, val) < 0) {
            return -1;
        }
        return 1;

    } else if (!strcmp(key, "vxlan.underlay.dip")) {
        if (__config_parse_spate_ip(&cfg->underlay_dip, val) < 0) {
            return -1;
        }
        return 1;

    } else if (!strcmp(key, "vxlan.underlay.sport")) {
        if (__config_parse_spate_port(&cfg->underlay_sport, val) < 0) {
            return -1;
        }
        return 1;

    } else if (!strcmp(key, "vxlan.overlay.smac")) {
        if (__config_parse_mac_addr(cfg->overlay_smac, val) < 0) {
            LOGE("config file's [vxlan.overlay.smac=%s] config error", val);
            return -1;
        }
        cfg->overlay_smac_is_setting = 1;
        return 1;
    }

    return 0;
}


const module_cfg_ops_t c_vxlan_cfg_ops = {
    .begin      = _vxlan_cfg_begin,
    .finish     = _vxlan_cfg_finish,
    .parse_line = _vxlan_cfg_parse_line,
};

