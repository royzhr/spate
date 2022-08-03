/*
 * Rodzhang
 *
 */

#include "linux_context_module.h"
#include "linux_context_alloctor_factory.h"
#include "../../plane_utils.h"


static int  _linux_context_module_init(void)
{
    __plane_context_alloctor_clean();

    g_plane->context_alloctor = plane_linux_context_alloctor_factory();
    if (!g_plane->context_alloctor) {
        return -1;
    }

    return 0;
}

static int  _linux_context_module_setting(void)
{
    return 0;
}

static void _linux_context_module_exit(void)
{
    __plane_context_alloctor_clean();
}

const module_class_t c_linux_context_module = {
    .module_name    = "linux_context",
    .cfg_ops        = NULL,
    .module_init    = _linux_context_module_init,
    .module_setting = _linux_context_module_setting,
    .module_exit    = _linux_context_module_exit,
};
