/*
 *  Rodzhang
 *
 */

#ifndef __SPATE_SERVER_STAT_H__
#define __SPATE_SERVER_STAT_H__


#include <stdint.h>


typedef struct {
    
    uint64_t                rx_pkts;

    uint64_t                tx_pkts;
    uint64_t                tx_busy_pkts;

} server_stat_info_traffic_t;

typedef struct {

    server_stat_info_traffic_t  traffic;

} server_stat_info_t;


static __inline void __server_stat_info_increase_traffic(server_stat_info_traffic_t *dstt, 
        const server_stat_info_traffic_t *inct)
{
    dstt->rx_pkts      += inct->rx_pkts;
    dstt->tx_pkts      += inct->tx_pkts;
    dstt->tx_busy_pkts += inct->tx_busy_pkts;
}

static __inline void __server_stat_info_increase(server_stat_info_t *dst,
        const server_stat_info_t *inc)
{
    __server_stat_info_increase_traffic(&dst->traffic, &inc->traffic);
}


#endif /* __SPATE_SERVER_STAT_H__ */
