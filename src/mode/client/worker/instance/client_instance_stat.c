/*
 * Rodzhang
 *
 */

#include "client_instance_stat.h"
#include <spate_utils.h>


static inline void __client_instance_rx_stat_traffic(client_stat_info_traffic_t *traffic)
{
    traffic->rx_pkts ++;
}

static inline void __client_instance_rx_stat_latency(client_stat_info_latency_t *latency, int us)
{
    uint16_t                    idx;

    idx = __spate_latency_slot_by_us(us);

    latency->cnt_tbl[idx] ++;
    latency->total_us += us;
}

void client_instance_stat_rx(client_instance_context_t *ctx, client_instance_rx_stat_param_t *sp)
{
    client_stat_info_t          *si;

    si = __ctx_get_client_stat_info(ctx);

    __client_instance_rx_stat_traffic(&si->traffic);
    __client_instance_rx_stat_latency(&si->latency, sp->us_latency);

    if (unlikely(sp->bug_code)) {
        si->traffic.bug_pkts ++;
    }
}


static inline void __client_instance_tx_stat_traffic(client_stat_info_traffic_t *traffic,
        uint16_t nr, uint16_t busy_nr)
{
    traffic->tx_pkts      += nr;
    traffic->tx_busy_pkts += busy_nr;
}

void client_instance_stat_tx(client_instance_context_t *ctx, uint16_t tx_nr, uint16_t busy_nr)
{
    client_stat_info_t          *si;

    si = __ctx_get_client_stat_info(ctx);
    
    __client_instance_tx_stat_traffic(&si->traffic, tx_nr, busy_nr);
}
