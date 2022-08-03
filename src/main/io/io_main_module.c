/*
 * Rodzhang
 *
 */

#include "io_main_module.h"
#include "io_main_mgr.h"
#include "io_log.h"
#include "io_redirect.h"



static int _io_main_module_init(__UNUSED__ int argc, __UNUSED__ char **argv)
{ 
    if (io_mgr_init() < 0) {
        return -1;
    }

    if (io_log_init() < 0) {
        return -1;
    }

    if (io_redirect_init() < 0) {
        return -1;
    }

    return 0;
}

static void _io_main_module_exit(void)
{
    io_redirect_exit();

    io_log_exit();

    io_mgr_exit();
}

const main_module_t c_io_main_module = {
    .name   = "main_io",
    .init   = _io_main_module_init,
    .exit   = _io_main_module_exit,
};


