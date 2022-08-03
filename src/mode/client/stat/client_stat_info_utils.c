/*
 *  Rodzhang
 *
 */

#include "client_stat_info_utils.h"
#include <math.h>



static __inline uint32_t __spate_latency_us_by_slot(int slot)
{
    if (slot >= 60) {
        return 10*1000*1000;
    }

    if (slot >= 50) {
        return (slot-50) *1000*1000 + 50000;
    }

    if (slot >= 40) {
        return  (slot-40) *1000*100 + 50000;
    }

    if (slot >= 30) {
        return  (slot-30) *1000*10 + 5000;
    }

    if (slot >= 20) {
        return  (slot-20) *1000 + 500;
    }
   
    if (slot >= 10) {
        return  (slot-10) *100 + 50;
    }

    return  (slot)*10 + 5;
}


double client_stat_info_latency_mean(const client_stat_info_t *ci)
{
    double              mean;

    if (!ci->traffic.rx_pkts) {
        return 0.0f;
    }

    mean = (double)ci->latency.total_us;
    mean /= ci->traffic.rx_pkts;

    return mean / 1000.0f;
}




double client_stat_info_latency_standard_deviation(const client_stat_info_t *ci)
{
    double              mean, sum, us, d;
    double              variance;
    double              standard_deviation;
    int                 mean_slot, i;

    if (ci->traffic.rx_pkts < 2) {
        return 0.0f;
    }

    mean = (double)ci->latency.total_us;
    mean /= ci->traffic.rx_pkts;

    mean_slot = __spate_latency_slot_by_us((int)mean);

    sum = 0.0f;

    for (i=0; i<CLIENT_STAT_LATENCY_NR; ++i) {
        if (i == mean_slot || i+1 == mean_slot || i-1==mean_slot) {
            continue;
        }
        
        if (ci->latency.cnt_tbl[i] == 0) {
            continue;
        }

        us = (double) __spate_latency_us_by_slot(i);
        
        d = (us - mean) * (us -mean);

        // LOGW("slot: %d-%d mean=%f, us=%f, delta=%f sd=%f", mean_slot, i, mean, us, us-mean, d);

        sum += d * ci->latency.cnt_tbl[i];
    }

    variance = sum / (ci->traffic.rx_pkts-1);

    standard_deviation = sqrt(variance);

    return standard_deviation / 1000.0f;
}

static uint64_t _get_tp_count(uint64_t total, double tp)
{
    double                  n;

    n = total * tp;

    return (uint64_t)n;
}

static uint64_t __client_stat_info_get_total(const client_stat_info_t *ci)
{
    uint64_t                total;
    int                     i;

    total = 0;

    for (i=0; i<CLIENT_STAT_LATENCY_NR; ++i) {
        total += ci->latency.cnt_tbl[i];
    }
    
    if (total != ci->traffic.rx_pkts) {
        LOGE("client_stat_info rx_pkts not-eq lantency.cnt_tbl[], %lu,%lu", 
                total, ci->traffic.rx_pkts);
    }


    return total;
}

static inline double __spate_latency_ms_by_slot(int slot)
{
    uint32_t                us;

    us = __spate_latency_us_by_slot(slot);

    return (double)us / 1000.0f;
}

void client_stat_info_latency_tp(const client_stat_info_t *ci, client_stat_latency_tp_t *tp)
{
    uint64_t                cnt_pt[CLIENT_STAT_LATENCY_TP_NR];
    uint64_t                total, c;
    int                     i, pt_idx;

    memset(tp, 0, sizeof(*tp));

    total = __client_stat_info_get_total(ci);
    if (total == 0) {
        return;
    }

    cnt_pt[0] = _get_tp_count(total, 0.50f);
    cnt_pt[1] = _get_tp_count(total, 0.90f);
    cnt_pt[2] = _get_tp_count(total, 0.95f);
    cnt_pt[3] = _get_tp_count(total, 0.99f);

    //LOGW("TP cnt: %lu %lu %lu %lu", cnt_pt[0], cnt_pt[1], cnt_pt[2], cnt_pt[3]);

    c      = 0;
    pt_idx = 0;

    for (i=0; i<CLIENT_STAT_LATENCY_NR; ++i) {
        c += ci->latency.cnt_tbl[i];

        for (; pt_idx<CLIENT_STAT_LATENCY_TP_NR; ++pt_idx) {
            if (c > cnt_pt[pt_idx]) {
                tp->tps[pt_idx] = __spate_latency_ms_by_slot(i);
            } else {
                break;
            }

            if (pt_idx == CLIENT_STAT_LATENCY_TP_NR) {
                break;
            }
        }
    }

    for (; pt_idx<CLIENT_STAT_LATENCY_TP_NR; ++pt_idx) {
        if (c > cnt_pt[pt_idx]) {
            tp->tps[pt_idx] = __spate_latency_ms_by_slot(i);
        } else {
            break;
        }
    }

    ASSERT(pt_idx == CLIENT_STAT_LATENCY_TP_NR);

}


