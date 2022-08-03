/*
 * Rodzhang
 *
 */

#include "host_cfg_ops.h"
#include "host_mgr.h"


static inline void __host_cfg_default(host_cfg_t *cfg)
{
    memset(cfg, 0, sizeof(*cfg));

    cfg->host_ip.cnt    = 0;

    cfg->arp_enable     = 1;
    cfg->icmp_enable    = 1;

    cfg->garp_enable      = 0;
    cfg->garp_vlan_enable = 0;
    cfg->garp_vlan_id     = 0;
}

static void _host_cfg_begin(void)
{
    host_cfg_t        *cfg;

    cfg = __host_cfg_block_get();

    __host_cfg_default(cfg);
}

static int _host_cfg_finish(void)
{
    host_cfg_t        *cfg;

    cfg = __host_cfg_block_get();

    __spate_cfg_ipv4_invalid_to_default(&cfg->host_ip);

    return 0;
}


static int _host_cfg_parse_line(const char *key, const char *val)
{
    host_cfg_t        *cfg;

    cfg = __host_cfg_block_get();

    if (!strcmp(key, "host.ip")) {
        if (__config_parse_spate_ip(&cfg->host_ip, val) < 0) {
            return -1;
        }
        return 1;

    } else if (!strcmp(key, "host.arp_enable")) {
        cfg->arp_enable = __config_parse_bool(val);
        return 1;

    } else if (!strcmp(key, "host.icmp_enable")) {
        cfg->icmp_enable = __config_parse_bool(val);
        return 1;

    } else if (!strcmp(key, "host.garp_enable")) {
        cfg->garp_enable = __config_parse_bool(val);
        return 1;

    } else if (!strcmp(key, "host.garp_vlan_enable")) {
        cfg->garp_vlan_enable = __config_parse_bool(val);
        return 1;

    } else if (!strcmp(key, "host.garp_vlan_id")) {
        cfg->garp_vlan_id = __config_parse_uint16(val);
        return 1;

    }

    return 0;
}

const module_cfg_ops_t c_host_cfg_ops = {
    .begin      = _host_cfg_begin,
    .finish     = _host_cfg_finish,
    .parse_line = _host_cfg_parse_line,
};


