/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_config.h>
#include <spate_main.h>
#include "pcap_cfg_ops.h"
#include "pcap_mgr.h"


static inline void __pcap_cfg_default(pcap_cfg_t *cfg)
{
    memset(cfg, 0, sizeof(*cfg));

    cfg->enable    = 0;
    cfg->rx_enable = 0;
    cfg->rx_enable = 0;
}

static void _pcap_cfg_begin(void)
{
    pcap_cfg_t        *cfg;

    cfg = __pcap_cfg_block_get();

    __pcap_cfg_default(cfg);
}

static int _pcap_cfg_finish(void)
{
    g_main->pcap_enable = (uint8_t)s_pcap_mgr->cfg.enable;

    return 0;
}


static int _pcap_cfg_parse_line(const char *key, const char *val)
{
    pcap_cfg_t        *cfg;

    cfg = __pcap_cfg_block_get();

    if (!strcmp(key, "pcap.enable")) {
        cfg->enable = __config_parse_bool(val);
        return 1;

    } else if (!strcmp(key, "pcap.file_prefix")) {
        cfg->file_prefix = strdup(val);
        return 1;

    } else if (!strcmp(key, "pcap.rx_enable")) {
        cfg->rx_enable = __config_parse_bool(val);
        return 1;

    } else if (!strcmp(key, "pcap.tx_enable")) {
        cfg->tx_enable = __config_parse_bool(val);
        return 1;

    } else if (!strcmp(key, "pcap.rx_filter")) {
        cfg->rx_filter_string = strdup(val);
        return 1;

    } else if (!strcmp(key, "pcap.tx_filter")) {
        cfg->tx_filter_string = strdup(val);
        return 1;

    }

    return 0;
}

const module_cfg_ops_t c_pcap_cfg_ops = {
    .begin      = _pcap_cfg_begin,
    .finish     = _pcap_cfg_finish,
    .parse_line = _pcap_cfg_parse_line,
};



