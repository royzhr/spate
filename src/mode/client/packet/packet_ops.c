/*
 *  Rodzhang
 *
 */

#include "packet_ops.h"
#include <spate_event.h>
#include "packet_mgr.h"


static int _packet_change_pps_per_worker(uint32_t pps_per_worker)
{
    g_packet->cfg.pps_per_worker = pps_per_worker;


    g_event->ops->trigger_event(EVENT_PPS_CHANGE, NULL);
    return 0;
}

const packet_ops_t c_packet_ops = {
    .change_pps_per_worker = _packet_change_pps_per_worker,
};

