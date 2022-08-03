/*
 * Rodzhang
 *
 */

#include <unistd.h>
#include <time.h>
#include <spate_main.h>
#include <spate_plane.h>
#include <spate_ctrl.h>
#include "tick_instance.h"
#include "tick_mgr.h"
#include <spate_utils.h>


static void _tick_call_notify()
{
    void (*fn)(void);

    if (s_tick_mgr->ticks < s_tick_mgr->notify_tick) {
        return;
    }

    fn = s_tick_mgr->notify_fn;

    s_tick_mgr->notify_fn   = NULL;
    s_tick_mgr->notify_tick = 0;

    fn();
}


static void _tick_instance_init(void)
{
    g_ctrl->sync->vptr->report_on_sync_wait(g_ctrl->sync, -2);

    LOGI("tick start ... ");
}

static void _tick_instance_exit(void)
{
}

static void _tick_instance_loop(void)
{
    for ( ; ; ) {
        
        if (g_main->force_quit) {
            break;
        }


        sleep(1);

        s_tick_mgr->ticks ++;

        if (unlikely(s_tick_mgr->notify_fn)) {
            _tick_call_notify();
        }
    }
}


void *tick_instance_run(__UNUSED__ void *arg)
{
    _tick_instance_init();

    _tick_instance_loop();

    _tick_instance_exit();

    return NULL;
}
