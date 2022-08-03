/*
 * Rodzhang
 *
 */

#include "server_stat_gather.h"
#include "../worker/server_worker.h"


void server_stat_gather(server_stat_t *ss)
{
    uint16_t                    i, nr;
    const server_stat_info_t    *w_info;

    nr = g_server_worker->ops->get_worker_nr();

    /*
     * Save NOW to LAST
     */
    server_stat_info_copy(&ss->info_last, &ss->info_now);

    /*
     * Update NOW
     */
    server_stat_info_zero(&ss->info_now);

    for (i=0; i<nr; ++i) {

        w_info = g_server_worker->ops->get_server_stat_info(i);

        __server_stat_info_increase(&ss->info_now, w_info);
    }

    /*
     * From Hook , such as ebpf-offload:
     */
    w_info = g_server_worker->ops->get_server_extend_stat_info();
    if (w_info) {
        __server_stat_info_increase(&ss->info_now, w_info);
    }
}
