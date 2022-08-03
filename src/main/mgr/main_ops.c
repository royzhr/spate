/*
 * Rodzhang
 *
 */

#include "main_ops.h"
#include "../cmdline/cmdline_export.h"


static spate_mode_e _main_get_mode(void)
{
    return g_cmdline->mode;
}

const main_ops_t c_main_ops = {
    .get_mode = _main_get_mode,
};
