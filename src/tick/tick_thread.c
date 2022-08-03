/*
 * Rodzhang
 *
 */

#include "tick_thread.h"
#include "tick_mgr.h"
#include "tick_instance.h"


int  tick_thread_init(void)
{
    return 0;
}

int  tick_thread_setting(void)
{
    int             ret;

    ret = pthread_create(&s_tick_mgr->thread, NULL, tick_instance_run, NULL);

    if (ret < 0) {
        return -1;
    }

    return 0;
}

void tick_thread_exit(void)
{
    pthread_join(s_tick_mgr->thread, NULL);
}

