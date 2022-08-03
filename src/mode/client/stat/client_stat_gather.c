/*
 * Rodzhang
 *
 */

#include "client_stat_gather.h"
#include "../worker/client_worker.h"



void client_stat_gather(client_stat_t *cs)
{
    uint16_t                    i, nr;
    const client_stat_info_t    *w_info;

    nr = g_client_worker->ops->get_worker_nr();

    /*
     * Save NOW to LAST
     */
    client_stat_info_copy(&cs->info_last, &cs->info_now);

    /*
     * Update NOW
     */
    client_stat_info_zero(&cs->info_now);

    /*
     * Get all worker's stat
     */
    for (i=0; i<nr; ++i) {

        w_info = g_client_worker->ops->get_client_stat_info(i);

        client_stat_info_increase(&cs->info_now, w_info);
    }

    /*
     * From Hook , such as ebpf-offload:
     */
    w_info = g_client_worker->ops->get_client_extend_stat_info();
    if (w_info) {
        client_stat_info_increase(&cs->info_now, w_info);
    }

}


