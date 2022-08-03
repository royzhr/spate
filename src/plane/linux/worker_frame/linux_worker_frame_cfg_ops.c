/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_config.h>
#include "linux_worker_frame_cfg.h"
#include "linux_worker_frame_cfg_ops.h"
#include "linux_worker_frame_utils.h"



static inline void __linux_worker_frame_cfg_default(linux_worker_frame_cfg_t *cfg)
{
    cfg->worker_nr       = 1;
    cfg->bind_cpu_begin  = 0;
    cfg->bind_cpu_enable = 0;
}


static void _linux_worker_frame_cfg_begin(void)
{
    linux_worker_frame_cfg_t       *cfg;

    cfg = __get_linux_worker_frame_cfg();

    __linux_worker_frame_cfg_default(cfg);
}

static int _linux_worker_frame_cfg_finish(void)
{
    linux_worker_frame_cfg_t       *cfg;

    cfg = __get_linux_worker_frame_cfg();

    if (cfg->worker_nr == 0 || cfg->worker_nr > SPATE_MAX_WORKER) {
        LOGW("worker frame's worker_nr illegal, adjusted to 1");
        cfg->worker_nr = 1;
    }

    return 0;
}

static int _linux_worker_frame_cfg_parse_line(const char *key, const char *val)
{
    linux_worker_frame_cfg_t       *cfg;

    cfg = __get_linux_worker_frame_cfg();

    if (!strcmp(key, "linux.worker.nr")) {
        cfg->worker_nr = __config_parse_uint16(val);
        return 1;

    } else if (!strcmp(key, "linux.worker.bind_cpu_enable")) {
        cfg->bind_cpu_enable = __config_parse_bool(val);
        return 1;

    } else if (!strcmp(key, "linux.worker.bind_cpu_begin")) {
        cfg->bind_cpu_begin = __config_parse_uint16(val);
        return 1;

    }

    return 0;
}

const module_cfg_ops_t c_linux_worker_frame_cfg_ops = {
    .begin      = _linux_worker_frame_cfg_begin,
    .finish     = _linux_worker_frame_cfg_finish,
    .parse_line = _linux_worker_frame_cfg_parse_line,
};
