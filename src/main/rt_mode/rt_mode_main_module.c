/*
 * Rodzhang
 *
 */


#include <spate_core.h>
#include <spate_mode.h>
#include "rt_mode_main_module.h"
#include "rt_mode_mgr.h"
#include "../cmdline/cmdline_export.h"



static int _rt_mode_main_module_init(__UNUSED__ int argc, __UNUSED__ char **argv)
{
    if (rt_mode_mgr_init() < 0) {
        return -1;
    }

    g_rt_mode->current_mode_ops = spate_mode_get_ops(g_cmdline->mode);

    if (!g_rt_mode->current_mode_ops) {
        LOGE("cant get mode_ops");
        return -1;
    }

    return 0;
}

static void _rt_mode_main_module_exit(void)
{
    spate_mode_put_ops(g_rt_mode->current_mode_ops);

    rt_mode_mgr_exit();
}

static void _rt_mode_main_module_run(void)
{
    ASSERT(s_rt_mode_mgr);

    g_rt_mode->current_mode_ops->mode_run();
}

const main_module_t c_rt_mode_main_module = {
    .name    = "main_rt_mode",
    .init    = _rt_mode_main_module_init,
    .exit    = _rt_mode_main_module_exit,
    .run     = _rt_mode_main_module_run,

};


