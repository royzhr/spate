/*
 *  Rodzhang
 *
 */

#include "client_http_bridge.h"
#include <spate_stat.h>
#include <spate_utils.h>
#include "cliet_http_change_pps.h"


static int _client_http_stat(const char *uri, char *buf, int size, int *len)
{
    stat_cmd_t                  cmd;
    int                         ret;

    memset(&cmd, 0, sizeof(cmd));

    cmd.uri      = uri;
    cmd.buf      = buf;
    cmd.buf_size = size;

    ret = g_stat->stat->vptr->on_cmd(g_stat->stat, &cmd);

    *len = cmd.buf_len;

    return ret;
}


/*
 * Return Val:
 * 1    : success and return 200OK
 * -1   : error and return 404
 * other: return 404
 */
int client_http_bridge_get(void *ud, const char *uri, char *buf, int size, int *len)
{
    if (!__strcmp_prex(uri, "/stat/")) {
        return _client_http_stat(uri, buf, size, len);
    
    } else if (!__strcmp_prex(uri, "/change_pps_per_worker")) {
        return client_http_change_pps(uri, buf, size, len);

    }

    return 0;
}


