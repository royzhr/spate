/*
 * Rodzhang
 *
 */

#include "cmdline_assign.h"
#include <spate_utils.h>


static spate_mode_e _cmdline_mode_select(cmdline_args_t *args)
{
    const char          *mode;

    if (args->version) {
        return SPATE_MODE_VERSION;
    } else if (args->show) {
        return SPATE_MODE_SHOW;
    } else if (args->log) {
        return SPATE_MODE_LOG;
    } else if (args->help) {
        goto help_mode;
    }

    mode = args->mode;

    if (mode) {
        if (!strcmp(mode, "client")) {
            return SPATE_MODE_CLIENT;
        } else if (!strcmp(mode, "server")) {
            return SPATE_MODE_SERVER;
        }
    } 

help_mode:
    return SPATE_MODE_HELP;
}


static void _cmdline_param_copy(cmdline_args_t *args)
{
    switch (g_cmdline->mode) {
        case SPATE_MODE_CLIENT:
        case SPATE_MODE_SERVER:
            break;

        default:
            return;
    }
    
    g_cmdline->config_file = args->config_file;

    if (!args->plane) {
        g_cmdline->plane_name = "linux";
    } else {
        char           *str;

        str = strdup(args->plane);
        __string_to_lower(str);

        g_cmdline->plane_name = str;
    }
}

int  cmdline_assign_init(void)
{
    cmdline_args_t      *args;

    args = &s_cmdline_mgr->args;

    g_cmdline->mode = _cmdline_mode_select(args);

    _cmdline_param_copy(args);

    return 0;
}

void cmdline_assign_exit(void)
{
}

