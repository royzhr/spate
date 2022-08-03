/*
 * Rodzhang
 *
 */

#include <spate_main.h>
#include <spate_ctrl.h>
#include <unistd.h>
#include "stat_instance.h"
#include "stat_mgr.h"




static void _stat_instance_init(void)
{

    early_mode_log();

    /*
     * Wait sync ready
     */
    g_ctrl->sync->vptr->report_on_sync_wait(g_ctrl->sync, -1);

}

static void _stat_instance_exit(void)
{
    //early_mode_log();
}



static void _stat_instance_loop(void)
{
    uint16_t        wait_time;
    uint16_t        now_time;
    stat_t          *stat;

    stat = g_stat->stat;

    wait_time = __stat_cfg_block_get()->flush_wait_time;
    now_time  = 0;

    for ( ; ; ) {
        
        sleep(1);

        if (g_main->force_quit) {
            break;
        }

        stat->vptr->on_tick(stat);

        now_time ++;

        if (now_time >= wait_time) {
            stat->vptr->on_flush(stat);
            now_time = 0;
        }

    }
}


void *stat_instance_run(__UNUSED__ void *arg)
{
    _stat_instance_init();

    _stat_instance_loop();

    _stat_instance_exit();

    return NULL;
}
