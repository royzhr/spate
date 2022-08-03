/*
 * Rodzhang
 *
 */

#include "linux_filter_module.h"
#include "linux_filter_factory.h"
#include "../plane_linux_utils.h"


static int  _linux_filter_module_init(void)
{

    return 0;
}

static int  _linux_filter_module_setting(void)
{
    plane_linux_t       *plane_linux;

    plane_linux = __get_plane_linux();

    plane_linux->filter = linux_filter_factory();
    if (!plane_linux->filter) {
        return -1;
    }

    return 0;
}

static void _linux_filter_module_exit(void)
{
    plane_linux_t       *plane_linux;

    plane_linux = __get_plane_linux();

    plane_linux->filter->vptr->destroy(plane_linux->filter);
    plane_linux->filter = NULL;
}

const module_class_t c_linux_filter_module = {
    .module_name    = "linux_filter",
    .cfg_ops        = NULL,
    .module_init    = _linux_filter_module_init,
    .module_setting = _linux_filter_module_setting,
    .module_exit    = _linux_filter_module_exit,
};
