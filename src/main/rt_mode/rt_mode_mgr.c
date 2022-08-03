/*
 * Rodzhang
 *
 */

#include "rt_mode_mgr.h"
#include <spate_mm.h>

rt_mode_export_t    *g_rt_mode     = NULL;
rt_mode_mgr_t       *s_rt_mode_mgr = NULL;

int  rt_mode_mgr_init(void)
{
    s_rt_mode_mgr = mm_vmalloc(sizeof(*s_rt_mode_mgr));

    if (!s_rt_mode_mgr) {
        return -1;
    }

    memset(s_rt_mode_mgr, 0, sizeof(*s_rt_mode_mgr));

    g_rt_mode = &s_rt_mode_mgr->_export;

    return 0;
}

void rt_mode_mgr_exit(void)
{
    mm_vfree(s_rt_mode_mgr, sizeof(*s_rt_mode_mgr));

    s_rt_mode_mgr = NULL;
    g_rt_mode     = NULL;

}

