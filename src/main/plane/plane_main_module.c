/*
 * Rodzhang
 *
 */


#include "plane_main_module.h"
#include "../cmdline/cmdline_export.h"
#include <spate_plane.h>



static int  _plane_main_module_init(int argc, char **argv)
{
    if (plane_singleton_add(g_cmdline->plane_name) < 0) {
        return -1;
    }

    ASSERT(g_plane);

    return g_plane->vptr->main_init(g_plane, argc, argv);
}

static void _plane_main_module_exit(void)
{
    g_plane->vptr->main_exit(g_plane);

    plane_singleton_clean();
}

const main_module_t c_plane_main_module = {
    .name    = "main_plane",
    .init    = _plane_main_module_init,
    .exit    = _plane_main_module_exit,
};


