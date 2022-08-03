/*
 * Rodzhang
 *
 */

#include "cmdline_main_module.h"
#include "cmdline_mgr.h"
#include "cmdline_parse.h"
#include "cmdline_assign.h"


static int  _cmdline_main_module_init(int argc, char **argv)
{
    int             ret;

    if (cmdline_mgr_init() < 0) {
        return -1;
    }

    ret = cmdline_parse_arg(argc, argv, &s_cmdline_mgr->args);

    if (ret < 0) {
        return -1;
    }

    if (cmdline_assign_init() < 0) {
        return -1;
    }

    return ret;
}

static void _cmdline_main_module_exit(void)
{
    cmdline_assign_exit();

    cmdline_mgr_exit();
}

const main_module_t c_cmdline_main_module = {
    .name    = "main_cmdline",
    .init    = _cmdline_main_module_init,
    .exit    = _cmdline_main_module_exit,
};

