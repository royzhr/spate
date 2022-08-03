/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_config.h>
#include <spate_utils.h>
#include <spate_debug.h>
#include "packet_cfg_ops.h"
#include "packet_mgr.h"

static inline void __packet_cfg_default(packet_cfg_t *cfg)
{
    memset(cfg, 0, sizeof(*cfg));

    cfg->payload_size   = SPATE_MIN_PAYLOAD;
    cfg->pps_per_worker = 1;
    cfg->burst_len      = 0;
    cfg->vlan_enable    = 0;
    cfg->vlan_id        = 0;
}


static void _packet_cfg_begin(void)
{
    packet_cfg_t       *cfg;

    cfg = __packet_cfg_block_get();

    __packet_cfg_default(cfg);
}

static void _packet_cfg_check_burst_len(packet_cfg_t *cfg)
{
    if (!cfg->burst_len)
        return;

    if (cfg->burst_len > cfg->pps_per_worker) {
        LOGW("config pkt_burst_len > pps_rate_per_worker , adjust pkt_burst_len to 0(auto)");
        goto set_default;
    }

    if (cfg->burst_len > SPATE_MAX_BURST) {
        LOGW("config pkt_burst_len > MaxBrust(%d) , adjust it to 0(auto)", SPATE_MAX_BURST);
        goto set_default;
    }

    if (!is_power_of_2(cfg->burst_len)) {
        LOGW("config pkt_burst_len must be power of 2, adjust it to 0(auto)");
        goto set_default;
    }

    return;

set_default:
    cfg->burst_len = 0;
    return;
}

static int _packet_cfg_finish(void)
{
    packet_cfg_t       *cfg;

    cfg = __packet_cfg_block_get();

    if (cfg->payload_size < SPATE_MIN_PAYLOAD) {
        cfg->payload_size = SPATE_MIN_PAYLOAD;
        LOGW("config pkt_payload_size must >= %d, adjust it to that value", SPATE_MIN_PAYLOAD);
    }
    
    if (cfg->payload_size > SPATE_MAX_PAYLOAD) {
        cfg->payload_size = SPATE_MAX_PAYLOAD;
        LOGW("config pkt_payload_size must <= %d, adjust it to that value", SPATE_MAX_PAYLOAD);
    }


    if (cfg->pps_per_worker == 0) {
        cfg->pps_per_worker = 1;
    }

    _packet_cfg_check_burst_len(cfg);

    return 0;
}

static int _packet_cfg_parse_line(const char *key, const char *val)
{
    packet_cfg_t       *cfg;

    cfg = __packet_cfg_block_get();

    if (!strcmp(key, "packet.payload_size")) {
        cfg->payload_size = __config_parse_uint16(val);
        return 1;

    } else if (!strcmp(key, "packet.pps_per_worker")) {
        cfg->pps_per_worker = __config_parse_uint32(val);
        return 1;

    } else if (!strcmp(key, "packet.dmac")) {
        if (__config_parse_mac_addr(cfg->dmac, val) < 0) {
            LOGE("config file's [packet.dmac=%s] config error", val);
            return -1;
        }
        return 1;

    } else if (!strcmp(key, "packet.burst_len")) {
        cfg->burst_len = __config_parse_uint16(val);
        return 1;

    } else if (!strcmp(key, "packet.vlan_enable")) {
        cfg->vlan_enable = __config_parse_bool(val);
        return 1;

    } else if (!strcmp(key, "packet.vlan_id")) {
        cfg->vlan_id = __config_parse_uint16(val);
        return 1;

    }

    return 0;
}


const module_cfg_ops_t c_packet_cfg_ops = {
    .begin      = _packet_cfg_begin,
    .finish     = _packet_cfg_finish,
    .parse_line = _packet_cfg_parse_line,
};

