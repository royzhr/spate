/*
 * Rodzhang
 *
 */

#include "early_mode_show.h"
#include <spate_plane.h>
#include <spate_print.h>


void early_mode_show(void)
{
    __spate_print("\n");

    plane_show_support();

    __spate_print("\n\n");
}

