/*
 *  Rodzhang
 *
 */


#include <spate_core.h>
#include <spate_config.h>
#include "http_cfg_ops.h"
#include "http_mgr.h"



static inline void __http_cfg_default(http_cfg_t *cfg)
{
    cfg->enable = 0;

    __spate_cfg_ipv4_invalid_to_default(&cfg->listen_ip);

    __spate_cfg_port_invalid_to_default(&cfg->listen_port);
}


static void _http_cfg_begin(void)
{
    http_cfg_t       *cfg;

    cfg = __http_cfg_block_get();

    __http_cfg_default(cfg);

}

static int _http_cfg_finish(void)
{
    return 0;
}

static int _http_cfg_parse_line(const char *key, const char *val)
{
    http_cfg_t       *cfg;

    cfg = __http_cfg_block_get();

    if (!strcmp(key, "http.listen_ip")) {
        if (__config_parse_spate_ip(&cfg->listen_ip, val) < 0) {
            return -1;
        }
        return 1;

    } else if (!strcmp(key, "http.listen_port")) {
        if (__config_parse_spate_port(&cfg->listen_port, val) < 0) {
            return -1;
        }
        return 1;

    } else if (!strcmp(key, "http.enable")) {
        cfg->enable = __config_parse_bool(val);
    }

    return 0;
}


const module_cfg_ops_t c_http_cfg_ops = {
    .begin      = _http_cfg_begin,
    .finish     = _http_cfg_finish,
    .parse_line = _http_cfg_parse_line,
};



