/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_config.h>
#include <spate_utils.h>
#include "client_stat_cfg_ops.h"


static inline client_stat_cfg_t *__client_stat_cfg_block_get(stat_t *my)
{
    client_stat_t       *cs;

    cs = container_of(my, client_stat_t, base);

    return &cs->client_cfg;
}

static inline void __client_stat_cfg_default(client_stat_cfg_t *cfg)
{
    memset(cfg, 0, sizeof(*cfg));

}

static void _client_stat_cfg_begin(stat_t *my)
{
    client_stat_cfg_t       *cfg;

    cfg = __client_stat_cfg_block_get(my);

    __client_stat_cfg_default(cfg);
}


static int _client_stat_cfg_finish(__UNUSED__ stat_t *my)
{
    return 0;
}



static int _client_stat_cfg_parse_line(stat_t *my, const char *key, const char *val)
{
    client_stat_cfg_t       *cfg;

    cfg = __client_stat_cfg_block_get(my);

    if (!strcmp(key, "stat_client_dummy")) {

        cfg->dummy = __config_parse_uint16(val);

        return 1;

    }

    return 0;
}

const stat_cfg_ops_t c_client_stat_cfg_ops = {
    .begin      = _client_stat_cfg_begin,
    .finish     = _client_stat_cfg_finish,
    .parse_line = _client_stat_cfg_parse_line,
};


