/*
 * Rodzhang
 *
 */


#include <spate_core.h>
#include <spate_config.h>
#include "stat_cfg.h"
#include "stat_cfg_ops.h"
#include "stat_mgr.h"
#include <spate_utils.h>



static inline void __stat_cfg_default(stat_cfg_t *cfg)
{
    cfg->flush_wait_time  = 1;
    cfg->worker_enable    = 0;
    cfg->max_history_time = 600;
}


static void _stat_cfg_begin(void)
{
    stat_cfg_t       *cfg;

    cfg = __stat_cfg_block_get();

    __stat_cfg_default(cfg);

    if (g_stat->stat->vptr->stat_cfg_ops) {
        g_stat->stat->vptr->stat_cfg_ops->begin(g_stat->stat);
    }
}

static int _stat_cfg_finish(void)
{
    stat_cfg_t       *cfg;

    cfg = __stat_cfg_block_get();

    if (g_stat->stat->vptr->stat_cfg_ops) {
        g_stat->stat->vptr->stat_cfg_ops->finish(g_stat->stat);
    }

    range_of(cfg->max_history_time, 60, 6000);

    return 0;
}

static int _stat_cfg_parse_line(const char *key, const char *val)
{
    stat_cfg_t       *cfg;

    cfg = __stat_cfg_block_get();

    if (!strcmp(key, "stat.flush_wait_time")) {
        cfg->flush_wait_time = __config_parse_uint16(val);
        return 1;

    } else if (!strcmp(key, "stat.worker_enable")) {
        cfg->worker_enable = __config_parse_bool(val);
        return 1;

    } else if (!strcmp(key, "stat.max_history_time")) {
        cfg->max_history_time = __config_parse_uint16(val);
        return 1;

    }

    if (g_stat->stat->vptr->stat_cfg_ops) {
        g_stat->stat->vptr->stat_cfg_ops->parse_line(g_stat->stat, key, val);
    }

    return 0;
}


const module_cfg_ops_t c_stat_cfg_ops = {
    .begin      = _stat_cfg_begin,
    .finish     = _stat_cfg_finish,
    .parse_line = _stat_cfg_parse_line,
};



