/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include "client_stat.h"
#include "client_stat_vtbl.h"
#include "client_stat_method.h"
#include "client_stat_cfg_ops.h"

#include "client_stat_gather.h"
#include "client_stat_print.h"
#include "cmd/client_stat_cmd.h"
#include <spate_utils.h>

static int _client_stat_setting(stat_t *my)
{
    client_stat_t           *cs;

    cs = container_of(my, client_stat_t, base);
    cs->history = client_stat_history_create();
    if (!cs->history) {
        return -1;
    }

    return 0;
}

static void _client_stat_on_tick(stat_t *my)
{
    client_stat_t           *cs;
    client_stat_history_t   *history;
    client_stat_info_t      delta;

    cs = container_of(my, client_stat_t, base);

    client_stat_gather(cs);
    
    client_stat_info_delta(&delta, &cs->info_now, &cs->info_last);

    history = cs->history;

    history->vptr->push_data(history, &delta);
}

static int _client_stat_on_flush(stat_t *my)
{
    client_stat_t           *cs;

    cs = container_of(my, client_stat_t, base);

    client_stat_flush_print(cs);

    return 0;
}

static int _client_stat_on_cmd(stat_t *my, stat_cmd_t *cmd)
{
    client_stat_t           *cs;

    cs = container_of(my, client_stat_t, base);

    return client_stat_cmd(cs, cmd);
}

static void _client_stat_destroy(stat_t *my)
{
    client_stat_t           *cs;

    cs = container_of(my, client_stat_t, base);

    client_stat_total_print(cs);

    client_stat_destructor(cs);

    mm_vfree(cs, sizeof(*cs));
}

const stat_vtbl_t c_client_stat_vtbl = {
    .setting      = _client_stat_setting,
    .on_tick      = _client_stat_on_tick,
    .on_flush     = _client_stat_on_flush,
    .on_cmd       = _client_stat_on_cmd,
    .destroy      = _client_stat_destroy,
    .stat_cfg_ops = &c_client_stat_cfg_ops,
};

