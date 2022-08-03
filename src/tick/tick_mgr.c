/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include <spate_main.h>
#include <spate_plane.h>
#include "tick_mgr.h"
#include "tick_ops.h"


tick_export_t   *g_tick     = NULL;
tick_mgr_t      *s_tick_mgr = NULL;


int  tick_mgr_init(void)
{
    s_tick_mgr = mm_vmalloc(sizeof(*s_tick_mgr));
    if (!s_tick_mgr) {
        return -1;
    }

    memset(s_tick_mgr, 0, sizeof(*s_tick_mgr));

    g_tick = &s_tick_mgr->_export;

    g_tick->ops = &c_tick_ops;


    return 0;
}

int  tick_mgr_setting(void)
{

    return 0;
}

void tick_mgr_exit(void)
{
    mm_vfree(s_tick_mgr, sizeof(*s_tick_mgr));

    s_tick_mgr = NULL;
    g_tick     = NULL;
}

