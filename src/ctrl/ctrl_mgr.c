/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include <spate_plane.h>
#include "ctrl_mgr.h"
#include "ctrl_thread.h"
#include "sync/sync_factory.h"


ctrl_export_t   *g_ctrl     = NULL;
ctrl_mgr_t      *s_ctrl_mgr = NULL;


int  ctrl_mgr_init(void)
{
    s_ctrl_mgr = mm_vmalloc(sizeof(*s_ctrl_mgr));
    if (!s_ctrl_mgr) {
        return -1;
    }

    memset(s_ctrl_mgr, 0, sizeof(*s_ctrl_mgr));

    g_ctrl = &s_ctrl_mgr->_export;

    ctrl_thread_init();

    return 0;
}

int  ctrl_mgr_setting(void)
{
    g_ctrl->sync = sync_create(__plane_get_worker_nr(), 2);
    if (!g_ctrl->sync) {
        return -1;
    }

    ctrl_thread_setting();

    return 0;
}

void ctrl_mgr_exit(void)
{
    ctrl_thread_exit();

    g_ctrl->sync->vptr->destroy(g_ctrl->sync);
    g_ctrl->sync = NULL;


    mm_vfree(s_ctrl_mgr, sizeof(*s_ctrl_mgr));

    s_ctrl_mgr = NULL;
    g_ctrl     = NULL;
}

