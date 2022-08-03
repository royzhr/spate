/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include "cmdline_mgr.h"


cmdline_export_t *g_cmdline      = NULL;
cmdline_mgr_t    *s_cmdline_mgr  = NULL;


int  cmdline_mgr_init(void)
{
    s_cmdline_mgr = mm_vmalloc(sizeof(*s_cmdline_mgr));

    if (!s_cmdline_mgr) {
        return -1;
    }

    memset(s_cmdline_mgr, 0, sizeof(*s_cmdline_mgr));

    g_cmdline = &s_cmdline_mgr->_export;

    return 0;
}

void cmdline_mgr_exit(void)
{
    mm_vfree(s_cmdline_mgr, sizeof(*s_cmdline_mgr));

    s_cmdline_mgr = NULL;
    g_cmdline     = NULL;
}
