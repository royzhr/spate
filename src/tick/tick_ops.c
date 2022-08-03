/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_main.h>
#include <spate_instance.h>
#include "tick_ops.h"
#include "tick_mgr.h"
#include <spate_utils.h>


static uint32_t _tick_get_tick(void)
{
    return s_tick_mgr->ticks;
}

static int _tick_add_notify(void (*fn)(void), uint32_t later)
{
    if (s_tick_mgr->notify_fn) {
        LOGE("tick notify already exists!");
        return -1;
    }

    s_tick_mgr->notify_fn   = fn;
    s_tick_mgr->notify_tick = later + s_tick_mgr->ticks + 1;

    return 0;
}


const tick_ops_t c_tick_ops = {
    .get_tick   = _tick_get_tick,
    .add_notify = _tick_add_notify,
};


