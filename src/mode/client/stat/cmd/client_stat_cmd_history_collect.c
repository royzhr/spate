/*
 *  Rodzhang
 *
 */

#include "client_stat_cmd_history_collect.h"



int client_stat_cmd_history_collect(client_stat_history_t *history,
        client_stat_info_t *info, int begin, int end)
{
    const client_stat_info_t        *ci;
    int                             i;

    client_stat_info_zero(info);

    for (i=begin; i<end; ++i) {
        ci = history->vptr->get_data(history, i);
        if (!ci) {
            return -1;
        }

        client_stat_info_increase(info, ci);
    }


    return 0;
}

