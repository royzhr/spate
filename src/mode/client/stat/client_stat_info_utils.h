/*
 *  Rodzhang
 *
 */

#ifndef __CLIENT_STAT_INFO_UTILS_H__
#define __CLIENT_STAT_INFO_UTILS_H__


#include "client_stat_info.h"

#define CLIENT_STAT_LATENCY_TP_NR   4

typedef struct {
    double          tps[CLIENT_STAT_LATENCY_TP_NR];
} client_stat_latency_tp_t;

/*
 * Return Value:
 * ms of latency mean|stanard_deviation
 */
double client_stat_info_latency_mean(const client_stat_info_t *ci);
double client_stat_info_latency_standard_deviation(const client_stat_info_t *ci);

void client_stat_info_latency_tp(const client_stat_info_t *ci, client_stat_latency_tp_t *tp);



#endif /* __CLIENT_STAT_INFO_UTILS_H__ */
