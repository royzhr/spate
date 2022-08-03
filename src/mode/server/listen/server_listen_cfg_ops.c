/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_config.h>
#include "server_listen_cfg.h"
#include "server_listen_mgr.h"


static inline void __server_listen_cfg_default(server_listen_cfg_t *cfg)
{
    memset(cfg, 0, sizeof(*cfg));

    cfg->vxlan_enable      = 0;
    cfg->listen_ip.cnt     = 1;
    cfg->listen_port.cnt   = 1;
    cfg->listen_proto_mask = SPATE_TCP | SPATE_UDP;

}

static void _server_listen_cfg_begin(void)
{
    server_listen_cfg_t        *cfg;

    cfg = __server_listen_cfg_block_get();

    __server_listen_cfg_default(cfg);
}

static int _server_listen_cfg_finish(void)
{
    server_listen_cfg_t        *cfg;

    cfg = __server_listen_cfg_block_get();

    __spate_cfg_ipv4_invalid_to_default(&cfg->listen_ip);
    __spate_cfg_port_invalid_to_default(&cfg->listen_port);

    if (!cfg->listen_proto_mask) {
        cfg->listen_proto_mask = SPATE_TCP | SPATE_UDP;
    }

    __spate_cfg_ipv4_invalid_to_default(&cfg->vxlan_vtep_ip);
    return 0;
}

static inline uint8_t __config_parse_proto_mask(const char *str)
{
    if (!strcmp(str, "tcp")) {
        return SPATE_TCP;
    } else if (!strcmp(str, "udp")) {
        return SPATE_UDP;
    } else if (!strcmp(str, "tcp,udp")) {
        return SPATE_UDP | SPATE_TCP;
    } else if (!strcmp(str, "udp,tcp")) {
        return SPATE_UDP | SPATE_TCP;
    }

    return 0;
}

static int _server_listen_cfg_parse_line(const char *key, const char *val)
{
    server_listen_cfg_t        *cfg;

    cfg = __server_listen_cfg_block_get();

    if (!strcmp(key, "server.listen.ip")) {
        if (__config_parse_spate_ip(&cfg->listen_ip, val) < 0) {
            return -1;
        }
        return 1;

    } else if (!strcmp(key, "server.listen.port")) {
        if (__config_parse_spate_port(&cfg->listen_port, val) < 0) {
            return -1;
        }
        return 1;

    } else if (!strcmp(key, "server.listen.proto")) {
        cfg->listen_proto_mask = __config_parse_proto_mask(val);
        return 1;

    } else if (!strcmp(key, "server.vxlan.enable")) {
        cfg->vxlan_enable = __config_parse_bool(val);
        return 1;

    } else if (!strcmp(key, "server.vxlan.vtep.ip")) {
        if (__config_parse_spate_ip(&cfg->vxlan_vtep_ip, val) < 0) {
            return -1;
        }
        return 1;
    }

    return 0;
}

const module_cfg_ops_t c_server_listen_cfg_ops = {
    .begin      = _server_listen_cfg_begin,
    .finish     = _server_listen_cfg_finish,
    .parse_line = _server_listen_cfg_parse_line,
};


