/*
 *  Rodzhang
 *
 * This .h file is used by both spate and ebpf-prog.
 */

#ifndef __SPATE_CLIENT_STAT_H__
#define __SPATE_CLIENT_STAT_H__


#include <stdint.h>


typedef struct {
    
    uint64_t                rx_pkts;

    uint64_t                tx_pkts;
    uint64_t                tx_busy_pkts;

    uint64_t                bug_pkts;

} client_stat_info_traffic_t;


#define CLIENT_STAT_LATENCY_NR    61

typedef struct {

    uint64_t                total_us;

    uint64_t                cnt_tbl[CLIENT_STAT_LATENCY_NR];

} client_stat_info_latency_t; 


static __inline uint16_t __spate_latency_slot_by_us(uint32_t us)
{
    uint16_t            idx;

    if (us < 100) {
        idx = us / 10;       //0.01ms
    } else if (us < 1000) {
        idx = 10 + us/100;   //0.1ms
    } else if (us < 10000) {
        idx = 20 + us/1000;  //1ms
    } else if (us < 100000) {
        idx = 30 + us/10000; //10ms
    } else if (us < 1000000) {
        idx = 40 + us/100000;//100ms
    } else if (us < 10000000) {
        idx = 50 + us/1000000;//1000ms
    } else {
        idx = 60;            //10000ms 
    }

    return idx;
}


static __inline void __client_stat_info_increase_traffic(client_stat_info_traffic_t *dstt, 
        const client_stat_info_traffic_t *inct)
{
    dstt->rx_pkts      += inct->rx_pkts;
    dstt->tx_pkts      += inct->tx_pkts;
    dstt->tx_busy_pkts += inct->tx_busy_pkts;
    dstt->bug_pkts     += inct->bug_pkts;
}


static __inline void __client_stat_info_increase_latency(client_stat_info_latency_t *dstl,
        const client_stat_info_latency_t *incl)
{
    uint16_t                    i;

    dstl->total_us += incl->total_us;

    for (i=0; i<CLIENT_STAT_LATENCY_NR; ++i) {
        dstl->cnt_tbl[i] += incl->cnt_tbl[i];
    }
}

#endif /* __SPATE_CLIENT_STAT_H__ */
