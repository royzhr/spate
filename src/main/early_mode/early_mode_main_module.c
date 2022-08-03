/*
 * Rodzhang
 *
 */


#include "early_mode_main_module.h"
#include "../cmdline/cmdline_export.h"
#include "early_mode_help.h"
#include "early_mode_version.h"
#include "early_mode_show.h"
#include "early_mode_log.h"


static int  _early_mode_main_module_init(__UNUSED__ int argc, __UNUSED__ char **argv)
{
    switch (g_cmdline->mode) {
        case SPATE_MODE_HELP:
            early_mode_help();
            return -1;

        case SPATE_MODE_VERSION:
            early_mode_version();
            return -1;

        case SPATE_MODE_SHOW:
            early_mode_show();
            return -1;

        case SPATE_MODE_LOG:
            early_mode_log();
            return -1;

        default:
            return 0;
    }

    return 0;
}

static void _early_mode_main_module_exit(void)
{

}

const main_module_t c_early_mode_main_module = {
    .name    = "main_early_mode",
    .init    = _early_mode_main_module_init,
    .exit    = _early_mode_main_module_exit,
};


