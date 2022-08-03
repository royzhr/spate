/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_config.h>
#include "fack_tcp_cfg_ops.h"
#include "fack_tcp_mgr.h"

#define FTCP_MAX_QUIT_GRACEFUL_TIMEOUT      60


static inline void __fack_tcp_cfg_default(fack_tcp_cfg_t *cfg)
{
    memset(cfg, 0, sizeof(*cfg));

    cfg->syn_retrans_time      = 3;
    cfg->fin_retrans_time      = 3;
    cfg->close_wait_time       = 5;
    cfg->establish_time        = 0;
    cfg->synack_ack_enable     = 0;
    cfg->quit_graceful_timeout = 0;
}

static void _fack_tcp_cfg_begin(void)
{
    fack_tcp_cfg_t       *cfg;

    cfg = __fack_tcp_cfg_block_get();

    __fack_tcp_cfg_default(cfg);
}


static int _fack_tcp_cfg_finish(void)
{
    return 0;
}



static int _fack_tcp_cfg_parse_line(const char *key, const char *val)
{
    fack_tcp_cfg_t       *cfg;

    cfg = __fack_tcp_cfg_block_get();

    if (!strcmp(key, "fack_tcp.syn_retrans_wait_time")) {
        cfg->syn_retrans_time = __config_parse_uint16(val);
        return 1;

    } else if (!strcmp(key, "fack_tcp.fin_retrans_wait_time")) {
        cfg->fin_retrans_time = __config_parse_uint16(val);
        return 1;

    } else if (!strcmp(key, "fack_tcp.close_wait_time")) {
        cfg->close_wait_time = __config_parse_uint16(val);
        return 1;

    } else if (!strcmp(key, "fack_tcp.establish_time")) {
        cfg->establish_time = __config_parse_uint16(val);
        return 1;

    } else if (!strcmp(key, "fack_tcp.synack_ack_enable")) {
        cfg->synack_ack_enable = __config_parse_bool(val);
        return 1;

    } else if (!strcmp(key, "fack_tcp.quit_graceful_timeout")) {
        cfg->quit_graceful_timeout = __config_parse_uint16(val);
        if (cfg->quit_graceful_timeout > FTCP_MAX_QUIT_GRACEFUL_TIMEOUT) {
            cfg->quit_graceful_timeout = FTCP_MAX_QUIT_GRACEFUL_TIMEOUT;
            LOGW("fack_tcp.quit_graceful_timeout cant more than %u, auto adjust to it", 
                    FTCP_MAX_QUIT_GRACEFUL_TIMEOUT);
        }

        return 1;

    }

    return 0;
}

const module_cfg_ops_t c_fack_tcp_cfg_ops = {
    .begin      = _fack_tcp_cfg_begin,
    .finish     = _fack_tcp_cfg_finish,
    .parse_line = _fack_tcp_cfg_parse_line,
};


