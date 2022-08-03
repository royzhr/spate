/*
 * Rodzhang
 *
 */

#include "server_instance_stat.h"

static inline void __server_instance_stat_traffic_inc(server_stat_info_traffic_t *traffic,
        uint16_t rx_nr, uint16_t tx_nr, uint16_t busy_nr)
{
    traffic->rx_pkts      += rx_nr;
    traffic->tx_pkts      += tx_nr;
    traffic->tx_busy_pkts += busy_nr;
}

void server_instance_on_stat_inc(server_instance_context_t *ctx,
        uint16_t rx_nr, uint16_t tx_nr, uint16_t busy_nr)
{
    server_stat_info_t          *si;

    si = __ctx_get_server_stat_info(ctx);

    __server_instance_stat_traffic_inc(&si->traffic, rx_nr, tx_nr, busy_nr);
}


static inline void __server_instance_stat_traffic_update(server_stat_info_traffic_t *traffic,
        uint64_t rx_nr, uint64_t tx_nr, uint64_t busy_nr)
{
    traffic->rx_pkts      = rx_nr;
    traffic->tx_pkts      = tx_nr;
    traffic->tx_busy_pkts = busy_nr;
}

void server_instance_on_stat_update(server_instance_context_t *ctx,
        uint64_t rx_nr, uint64_t tx_nr, uint64_t busy_nr)
{
    server_stat_info_t          *si;

    si = __ctx_get_server_stat_info(ctx);

    __server_instance_stat_traffic_update(&si->traffic, rx_nr, tx_nr, busy_nr);
}


