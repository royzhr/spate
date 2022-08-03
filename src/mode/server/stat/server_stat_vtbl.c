/*
 * Rodzhang
 *
 */


#include <spate_mm.h>
#include "server_stat.h"
#include "server_stat_vtbl.h"
#include "server_stat_method.h"
#include "server_stat_gather.h"
#include "server_stat_print.h"
#include <spate_utils.h>

static int _server_stat_setting(stat_t *my)
{
    return 0;
}

static void _server_stat_on_tick(stat_t *my)
{
}

static int _server_stat_on_flush(stat_t *my)
{
    server_stat_t       *ss;

    ss = container_of(my, server_stat_t, base);

    server_stat_gather(ss);

    server_stat_print(ss);

    return 0;
}

static int _server_stat_on_cmd(stat_t *my, stat_cmd_t *cmd)
{
    server_stat_t       *ss;

    ss = container_of(my, server_stat_t, base);

    LOGW("server stat on flush %p, cmd:%p", ss, cmd);
    return 0;
}

static void _server_stat_destroy(stat_t *my)
{
    server_stat_t       *ss;

    ss = container_of(my, server_stat_t, base);

    server_stat_destructor(ss);

    mm_vfree(ss, sizeof(*ss));
}

const stat_vtbl_t c_server_stat_vtbl = {
    .setting      = _server_stat_setting,
    .on_tick      = _server_stat_on_tick,
    .on_flush     = _server_stat_on_flush,
    .on_cmd       = _server_stat_on_cmd,
    .destroy      = _server_stat_destroy,
    .stat_cfg_ops = NULL,
};

