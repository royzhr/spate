/*
 *  Rodzhang
 *
 */

#include "client_worker_event_pps.h"
#include <spate_packet.h>
#include "../client_worker_mgr.h"
#include "../client_worker_traffic_ctrl.h"
#include <spate_utils.h>


int client_worker_event_on_pps_change(void *ud, void *args)
{

    uint16_t                    worker_nr, i;
    client_instance_context_t   *ctx;

    worker_nr = s_client_worker_mgr->worker_nr;

    for (i=0; i<worker_nr; ++i) {
        ctx = &s_client_worker_mgr->contexts[i];

        client_traffic_controller_setting(&ctx->tc);
    }

    SMP_MB();

    //LOGW("worker event pps changed pps=%d", g_packet->cfg.pps_per_worker);

    return 0;
}


