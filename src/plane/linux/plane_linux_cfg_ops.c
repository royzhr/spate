/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_config.h>
#include <spate_module.h>
#include "plane_linux_cfg_ops.h"
#include "plane_linux_sub_modules.h"
#include "plane_linux_extend_module.h"


static void _plane_linux_cfg_begin(void)
{
    spate_modules_cfg_begin(c_linux_sub_modules);
    
    plane_linux_extend_module_cfg_begin();
}

static int _plane_linux_cfg_finish(void)
{
    int                 ret;

    ret = spate_modules_cfg_finish(c_linux_sub_modules);
    if (ret < 0) {
        return ret;
    }

    return plane_linux_extend_module_cfg_finish();
}

static int _plane_linux_cfg_parse_line(const char *key, const char *val)
{
    int                 ret;

    ret = spate_modules_cfg_parse_line(key, val, c_linux_sub_modules);
    if (ret) {
        return ret;
    }

    return plane_linux_extend_module_cfg_parse_line(key, val);
}

const module_cfg_ops_t c_plane_linux_cfg_ops = {
    .begin      = _plane_linux_cfg_begin,
    .finish     = _plane_linux_cfg_finish,
    .parse_line = _plane_linux_cfg_parse_line,
};

