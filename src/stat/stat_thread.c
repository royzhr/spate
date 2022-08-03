/*
 * Rodzhang
 *
 */

#include "stat_thread.h"
#include "stat_mgr.h"
#include "stat_instance.h"


int  stat_thread_init(void)
{
    return 0;
}

int  stat_thread_setting(void)
{
    int             ret;

    LOGD("stat thread init");

    ret = pthread_create(&s_stat_mgr->stat_thread, NULL, stat_instance_run, NULL);

    if (ret < 0) {
        return -1;
    }

    return 0;
}

void stat_thread_exit(void)
{
    LOGD("stat thread exit");

    pthread_join(s_stat_mgr->stat_thread, NULL);
}



