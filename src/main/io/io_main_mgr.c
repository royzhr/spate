/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include "io_main_mgr.h"
#include "io_main_ops.h"


io_export_t     *g_io     = NULL;
io_mgr_t        *s_io_mgr = NULL;


int  io_mgr_init(void)
{
    s_io_mgr = mm_vmalloc(sizeof(*s_io_mgr));
    if (!s_io_mgr) {
        return -1;
    }

    memset(s_io_mgr, 0, sizeof(*s_io_mgr));

    g_io = &s_io_mgr->_export;

    g_io->ops = &c_io_ops;

    return 0;
}

void io_mgr_exit(void)
{
    mm_vfree(s_io_mgr, sizeof(*s_io_mgr));

    s_io_mgr = NULL;
    g_io     = NULL;
}


