/*
 * Rodzhang
 *
 */

#include "plane_linux_vtbl.h"
#include "plane_linux_method.h"
#include <spate_mm.h>
#include <spate_utils.h>


static int _plane_linux_main_init(__UNUSED__ plane_t *my, 
        __UNUSED__ int argc, __UNUSED__ char **argv)
{


    return 0;
}

static void _plane_linux_main_exit(__UNUSED__ plane_t *my)
{
}

static void _plane_linux_main_destroy(plane_t *my)
{
    plane_linux_t       *lix;

    lix = container_of(my, plane_linux_t, base);

    plane_linux_destructor(lix);

    mm_vfree(lix, sizeof(*lix));
}

const plane_vtbl_t c_plane_linux_vtbl = {
    .main_init = _plane_linux_main_init,
    .main_exit = _plane_linux_main_exit,
    .destroy   = _plane_linux_main_destroy,
};

