/*
 *  Rodzhang
 *
 */

#include "client_stat_cmd_history.h"
#include "client_stat_cmd_history_collect.h"
#include "client_stat_cmd_history_output.h"
#include <spate_http.h>
#include <spate_config.h>
#include <spate_utils.h>




static inline int __client_stat_history_range_parse_uri(const char *uri, int *begin, int *end)
{
    char                        val[SPATE_URI_PARAMS_SIZE];
    char                        val2[SPATE_URI_PARAMS_SIZE];
    int                         ret, ret2;

    ret = http_parse_uri_params(uri, "idx", val, SPATE_URI_PARAMS_SIZE);
    if (!ret) {
        *begin = __config_parse_uint16(val);
        *end   = *begin + 1;
        return 0;
    }

    ret  = http_parse_uri_params(uri, "begin", val, SPATE_URI_PARAMS_SIZE);
    ret2 = http_parse_uri_params(uri, "end", val2, SPATE_URI_PARAMS_SIZE);
    
    if (!ret && !ret2) {
        *begin = __config_parse_uint16(val);
        *end   = __config_parse_uint16(val2);
        return 0;
    }
    
    return -1;
}

static int _client_stat_history_range_parse_uri(const char *uri, int total, int *begin, int *end)
{
    int                         ret;

    ret = __client_stat_history_range_parse_uri(uri, begin, end);
    if (ret < 0) {
        return ret;
    }

    if (*begin >= *end) {
        return -1;
    }

    if (*begin>=total || *end>total) {
        return -1;
    }

    //LOGW("range total: %d, begin %d, end:%d", total, *begin, *end);

    return 0;
}

static int _client_stat_history_last_parse_uri(const char *uri, int total, int *begin, int *end)
{
    char                        val[SPATE_URI_PARAMS_SIZE];
    int                         ret;
    int                         n;

    ret = http_parse_uri_params(uri, "count", val, SPATE_URI_PARAMS_SIZE);
    if (ret) {
        return -1;
    }

    n = __config_parse_uint16(val);

    if (n<=0 || n>total) {
        return -1;
    }

    *begin = total - n;
    *end   = *begin + n;

    //LOGW("last total: %d, begin %d, end:%d", total, *begin, *end);

    return 0;
}

static int _client_stat_history_get_tick(client_stat_history_t *history, 
        const char *uri, int *begin, int *end)
{
    int                         total;

    total = history->vptr->get_current_total(history);

    if (!__strcmp_prex(uri, "/stat/history_last")) {
        return _client_stat_history_last_parse_uri(uri, total, begin, end);

    } else if (!__strcmp_prex(uri, "/stat/history_range")) {

        return _client_stat_history_range_parse_uri(uri, total, begin, end);
    }

    return -1;
}


int client_stat_cmd_history(client_stat_t *cs, stat_cmd_t *cmd)
{
    client_stat_history_t       *history;
    int                         begin, end;
    int                         ret;
    client_stat_info_t          info;
    
    history = cs->history;

    ret = _client_stat_history_get_tick(history, cmd->uri, &begin, &end);
    if (ret < 0) {
        stat_cmd_build_error(cmd, -10023);
        return -1;
    }

    ret = client_stat_cmd_history_collect(history, &info, begin, end);
    if (ret < 0) {
        stat_cmd_build_error(cmd, -10024);
        return -1;
    }

    ret = client_stat_cmd_history_output(cmd, &info, begin, end);
    if (ret < 0) {
        stat_cmd_build_error(cmd, -10025);
        return -1;
    }

    return ret;
}

