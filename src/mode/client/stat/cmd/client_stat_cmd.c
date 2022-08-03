/*
 *  Rodzhang
 *
 */

#include "client_stat_cmd.h"
#include "client_stat_cmd_history.h"
#include <spate_utils.h>


static int _client_stat_cmd_history_total(client_stat_t *cs, stat_cmd_t *cmd)
{
    client_stat_history_t       *history;
    char                        *buf;
    int                         len;
    int                         total, max;
    
    history = cs->history;

    total = history->vptr->get_current_total(history);
    max   = g_stat->stat->cfg.max_history_time;

    len = 0;
    buf = cmd->buf;

    len += sprintf(buf+len, "{\r\n");
    len += sprintf(buf+len, "\t\"Error\": 0,\r\n");
    len += sprintf(buf+len, "\t\"Total\": %d,\r\n", total);
    len += sprintf(buf+len, "\t\"Max\": %d\r\n", max);
    len += sprintf(buf+len, "}\r\n");

    cmd->buf_len = len;

    return 1;
}

/*
 *
 * 
 */
int client_stat_cmd(client_stat_t *cs, stat_cmd_t *cmd)
{
    const char              *uri;

    uri = cmd->uri;

    if (!__strcmp_prex(uri, "/stat/current_total")) {
        return _client_stat_cmd_history_total(cs, cmd);
    
    } else if (!__strcmp_prex(uri, "/stat/history")) {
        return client_stat_cmd_history(cs, cmd);
    
    }

    stat_cmd_build_error(cmd, -1);

    return -1;
}


