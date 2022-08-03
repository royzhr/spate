/*
 * Rodzhang
 *
 */

#include "ctrl_instance.h"
#include "ctrl_mgr.h"
#include <spate_utils.h>



void *ctrl_instance_run(__UNUSED__ void *arg)
{
    ASSERT(g_ctrl->sync);

    for ( ; ; ) {
        if (g_ctrl->sync->vptr->is_all_report(g_ctrl->sync)) {
            break;
        }
    }

    //LOGD("******** all report!");

    __spate_msleep(100);

    g_ctrl->sync->vptr->wake_all_waiter(g_ctrl->sync);

    return NULL;
}

