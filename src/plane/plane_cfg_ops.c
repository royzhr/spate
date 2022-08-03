/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_config.h>
#include "plane.h"
#include "plane_cfg_ops.h"


static void _plane_cfg_begin(void)
{
    g_plane->module_class->cfg_ops->begin();
}

static int _plane_cfg_finish(void)
{
    return g_plane->module_class->cfg_ops->finish();
}


static int _plane_cfg_parse_line(const char *key, const char *val)
{
    return g_plane->module_class->cfg_ops->parse_line(key, val);
}

const module_cfg_ops_t c_plane_cfg_ops = {
    .begin      = _plane_cfg_begin,
    .finish     = _plane_cfg_finish,
    .parse_line = _plane_cfg_parse_line,
};



