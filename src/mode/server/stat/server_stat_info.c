/*
 * Rodzhang
 *
 */


#include "server_stat_info.h"

void server_stat_info_zero(server_stat_info_t *cs)
{
    memset(cs, 0, sizeof(*cs));
}


void server_stat_info_copy(server_stat_info_t *dst, 
        const server_stat_info_t *src)
{
    memcpy(dst, src, sizeof(*dst));
}



static inline void __server_stat_info_delta_traffic(server_stat_info_traffic_t *delta, 
        const server_stat_info_traffic_t *new, const server_stat_info_traffic_t *old)
{
    delta->rx_pkts      = new->rx_pkts - old->rx_pkts;
    delta->tx_pkts      = new->tx_pkts - old->tx_pkts;
    delta->tx_busy_pkts = new->tx_busy_pkts - old->tx_busy_pkts;
}


void server_stat_info_delta(server_stat_info_t *delta, 
        const server_stat_info_t *new, const server_stat_info_t *old)
{
    __server_stat_info_delta_traffic(&delta->traffic, &new->traffic, &old->traffic);
}


