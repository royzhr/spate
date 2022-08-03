/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_config.h>
#include "session_cfg_ops.h"
#include "session_mgr.h"


static inline void __session_cfg_default(session_cfg_t *cfg)
{
    memset(cfg, 0, sizeof(*cfg));

    cfg->sip.cnt   = 1;
    cfg->dip.cnt   = 1;
    cfg->sport.cnt = 1;
    cfg->dport.cnt = 1;
    cfg->proto     = SPATE_UDP;
    
    cfg->table_split_by_worker = 1;
    cfg->table_show            = 0;
    cfg->table_shuffle         = 0;
}

static void _session_cfg_begin(void)
{
    session_cfg_t       *cfg;

    cfg = __session_cfg_block_get();

    __session_cfg_default(cfg);
}


static int _session_cfg_finish(void)
{
    session_cfg_t       *cfg;

    cfg = __session_cfg_block_get();

    __spate_cfg_ipv4_invalid_to_default(&cfg->sip);
    __spate_cfg_ipv4_invalid_to_default(&cfg->dip);

    __spate_cfg_port_invalid_to_default(&cfg->sport);
    __spate_cfg_port_invalid_to_default(&cfg->dport);

    if (cfg->proto == SPATE_UNKNOW) {
        cfg->proto = SPATE_UDP;
        LOGW("session.proto is unknow, adjust to UDP");
    }

    return 0;
}


static inline spate_proto_e __session_parse_proto(const char *str)
{
    if (!strcmp(str, "tcp")) {
        return SPATE_TCP;
    } else if (!strcmp(str, "udp")) {
        return SPATE_UDP;
    } else {
        return SPATE_UNKNOW;
    }
}


static int _session_cfg_parse_line(const char *key, const char *val)
{
    session_cfg_t       *cfg;

    cfg = __session_cfg_block_get();

    if (!strcmp(key, "session.sip")) {
        if (__config_parse_spate_ip(&cfg->sip, val) < 0) {
            return -1;
        }
        return 1;

    } else if (!strcmp(key, "session.dip")) {
        if (__config_parse_spate_ip(&cfg->dip, val) < 0) {
            return -1;
        }
        return 1;

    } else if (!strcmp(key, "session.sport")) {
        if (__config_parse_spate_port(&cfg->sport, val) < 0) {
            return -1;
        }
        return 1;

    } else if (!strcmp(key, "session.dport")) {
        if (__config_parse_spate_port(&cfg->dport, val) < 0) {
            return -1;
        }
        return 1;

    } else if (!strcmp(key, "session.proto")) {
        cfg->proto = __session_parse_proto(val);
        return 1;

    } else if (!strcmp(key, "session.table_shuffle")) {
        cfg->table_shuffle = __config_parse_bool(val);
        return 1;

    } else if (!strcmp(key, "session.table_show")) {
        cfg->table_show = __config_parse_bool(val);
        return 1;

    } else if (!strcmp(key, "session.table_split_by_worker")) {
        cfg->table_split_by_worker = __config_parse_bool(val);
        return 1;


    }

    return 0;
}

const module_cfg_ops_t c_session_cfg_ops = {
    .begin      = _session_cfg_begin,
    .finish     = _session_cfg_finish,
    .parse_line = _session_cfg_parse_line,
};


