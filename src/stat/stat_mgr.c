/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include <spate_main.h>
#include "stat_mgr.h"


stat_export_t   *g_stat         = NULL;
stat_mgr_t       *s_stat_mgr    = NULL;


int  stat_mgr_init(void)
{
    s_stat_mgr = mm_vmalloc(sizeof(*s_stat_mgr));

    if (!s_stat_mgr) {
        return -1;
    }

    memset(s_stat_mgr, 0, sizeof(*s_stat_mgr));

    g_stat = &s_stat_mgr->_export;

    g_stat->stat = g_rt_mode->current_mode_ops->mode_create_stat();
    if (!g_stat->stat) {
        LOGE("cant create stat");
        return -1;
    }

    return 0;
}

int  stat_mgr_setting(void)
{
    if (g_stat->stat->vptr->setting(g_stat->stat) < 0) {
        LOGE("stat setting error");
        return -1;
    }

    return 0;
}

void stat_mgr_exit(void)
{
    ASSERT(s_stat_mgr);

    g_stat->stat->vptr->destroy(g_stat->stat);

    mm_vfree(s_stat_mgr, sizeof(*s_stat_mgr));

    g_stat     = NULL;
    s_stat_mgr = NULL;
}



