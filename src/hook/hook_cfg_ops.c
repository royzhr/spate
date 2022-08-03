/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_config.h>
#include <spate_utils.h>
#include <spate_debug.h>
#include "hook_cfg_ops.h"
#include "hook_mgr.h"


static inline void __hook_cfg_default(hook_cfg_t *cfg)
{
    memset(&cfg, 0, sizeof(*cfg));

}

static void _hook_cfg_begin(void)
{
    hook_cfg_t          *cfg;

    cfg = __hook_cfg_block_get();

    __hook_cfg_default(cfg);
}

static int _hook_cfg_finish(void)
{
    return 0;
}

static int _hook_cfg_parse_line(const char *key, const char *val)
{
    hook_cfg_t          *cfg;

    cfg = __hook_cfg_block_get();

    if (!strcmp(key, "hook_tx_dmac")) {
        if (__config_parse_mac_addr(cfg->tx_dmac, val) < 0) {
            LOGW("config file's [%s = %s] config error", key, val);
            return 1;
        }
        cfg->tx_dmac_enable = 1;

        char    str[128];
        
        __mac_addr_to_string(cfg->tx_dmac, str, 128);
        LOGD("HOOK dmac: %s", str);

        return 1;
    }

    return 0;
}


const module_cfg_ops_t c_hook_cfg_ops = {
    .begin      = _hook_cfg_begin,
    .finish     = _hook_cfg_finish,
    .parse_line = _hook_cfg_parse_line,
};
