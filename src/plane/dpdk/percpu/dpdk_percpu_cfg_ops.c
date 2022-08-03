/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_config.h>
#include <spate_utils.h>
#include "dpdk_percpu_cfg.h"
#include "dpdk_percpu_cfg_ops.h"
#include "dpdk_percpu_mgr.h"


static inline dpdk_percpu_cfg_t *__get_dpdk_percpu_cfg()
{
    dpdk_percpu_mgr_t       *mgr;

    mgr = __get_dpdk_percpu_mgr();

    return &mgr->_export.cfg;
}


static inline void __dpdk_percpu_cfg_default(dpdk_percpu_cfg_t *cfg)
{
    cfg->mbuf_pool_size = 0;
}


static void _dpdk_percpu_cfg_begin(void)
{
    dpdk_percpu_cfg_t       *cfg;

    cfg = __get_dpdk_percpu_cfg();

    __dpdk_percpu_cfg_default(cfg);
}

static int _dpdk_percpu_cfg_finish(void)
{
    return 0;
}

static int _dpdk_percpu_cfg_parse_line(const char *key, const char *val)
{
    dpdk_percpu_cfg_t       *cfg;

    cfg = __get_dpdk_percpu_cfg();

    if (!strcmp(key, "dpdk.mbuf_pool_size")) {

        cfg->mbuf_pool_size = __config_parse_uint32(val);
        return 1;
    }

    return 0;
}

const module_cfg_ops_t c_dpdk_percpu_cfg_ops = {
    .begin      = _dpdk_percpu_cfg_begin,
    .finish     = _dpdk_percpu_cfg_finish,
    .parse_line = _dpdk_percpu_cfg_parse_line,
};
