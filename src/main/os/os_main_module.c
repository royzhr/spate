/*
 * Rodzhang
 *
 */

#include "os_main_module.h"
#include "os_signal.h"
#include "os_mgr.h"


static int  _os_main_module_init(__UNUSED__ int argc, __UNUSED__ char **argv)
{
    if (os_mgr_init() < 0) {
        return -1;
    }

    if (os_signal_init() < 0) {
        return -1;
    }

    return 0;
}

static void _os_main_module_exit(void)
{
    os_signal_exit();

    os_mgr_exit();
}

const main_module_t c_os_main_module = {
    .name    = "main_os",
    .init    = _os_main_module_init,
    .exit    = _os_main_module_exit,
};


