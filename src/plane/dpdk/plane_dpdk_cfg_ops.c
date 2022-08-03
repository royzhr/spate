/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_config.h>
#include <spate_module.h>
#include "plane_dpdk_cfg_ops.h"
#include "plane_dpdk_sub_modules.h"


static void _plane_dpdk_cfg_begin(void)
{
    spate_modules_cfg_begin(c_dpdk_sub_modules);
}

static int _plane_dpdk_cfg_finish(void)
{
    return spate_modules_cfg_finish(c_dpdk_sub_modules);
}


static int _plane_dpdk_cfg_parse_line(const char *key, const char *val)
{
    return spate_modules_cfg_parse_line(key, val, c_dpdk_sub_modules);
}

const module_cfg_ops_t c_plane_dpdk_cfg_ops = {
    .begin      = _plane_dpdk_cfg_begin,
    .finish     = _plane_dpdk_cfg_finish,
    .parse_line = _plane_dpdk_cfg_parse_line,
};




