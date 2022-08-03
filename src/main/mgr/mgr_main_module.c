/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include "mgr_main_module.h"
#include "main_mgr.h"


static int _mgr_main_module_init(__UNUSED__ int argc, __UNUSED__ char **argv)
{
    if (main_mgr_init() < 0) {
        return -1;
    }

    return 0;
}

static void _mgr_main_module_exit(void)
{
    main_mgr_exit();
}

const main_module_t c_mgr_main_module = {
    .name    = "main_mgr",
    .init    = _mgr_main_module_init,
    .exit    = _mgr_main_module_exit,
};

