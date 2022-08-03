/*
 *  Rodzhang
 *
 */

#include "client_worker_traffic_ctrl.h"
#include <spate_core.h>
#include <spate_packet.h>
#include <spate_plane.h>

/*
 * get brust-value according nr
 */
static inline uint16_t __traffic_select_suitable_burst(uint32_t nr)
{
    ASSERT(1024 == SPATE_MAX_BURST);

    if (nr <= 1000) {
        return 1;
    } else if (nr <= 4*1000) {
        return 2; 
    } else if (nr <= 8*1000) {
        return 4;
    } else if (nr <= 16*1000) {
        return 8;
    } else if (nr <= 32*1000) {
        return 16;
    } else if (nr <= 64*1000) {
        return 32;
    } else if (nr <= 128*1000) {
        return 64;
    } else if (nr <= 256*1000) {
        return 128;
    } else if (nr <= 512*1000) {
        return 256;
    } else if (nr <= 1024*1000) {
        return 512;
    }

    return SPATE_MAX_BURST;
}

void client_traffic_controller_setting(traffic_controller_t *tc)
{
    uint32_t                pps;
    uint32_t                period;
    uint16_t                burst_nr;
    uint64_t                cycles, hz;

    pps      = g_packet->cfg.pps_per_worker;
    burst_nr = g_packet->cfg.burst_len;

    if (burst_nr) {
        ASSERT(burst_nr <= SPATE_MAX_BURST);
        ASSERT(is_power_of_2(burst_nr));
    } else {
        burst_nr = __traffic_select_suitable_burst(pps);
    }
    period   = pps / burst_nr;
    hz       = __plane_get_hz();
    cycles   = hz / period;
    
    tc->tx_burst_nr     = burst_nr;
    tc->tx_burst_cycles = cycles;
}





