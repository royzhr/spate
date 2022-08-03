/*
 * Rodzhang
 *
 */

#include "ctrl_thread.h"
#include "ctrl_mgr.h"
#include "ctrl_instance.h"


int  ctrl_thread_init(void)
{
    return 0;
}

int  ctrl_thread_setting(void)
{
    int                 ret;

    ret = pthread_create(&s_ctrl_mgr->ctrl_thread, NULL, ctrl_instance_run, NULL);

    if (ret < 0) {
        return -1;
    }

    return 0;
}

void ctrl_thread_exit(void)
{
    pthread_join(s_ctrl_mgr->ctrl_thread, NULL);
}


