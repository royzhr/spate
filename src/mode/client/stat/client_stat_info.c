/*
 * Rodzhang
 *
 */

#include "client_stat_info.h"


void client_stat_info_zero(client_stat_info_t *cs)
{
    memset(cs, 0, sizeof(*cs));
}


void client_stat_info_copy(client_stat_info_t *dst, 
        const client_stat_info_t *src)
{
    memcpy(dst, src, sizeof(*dst));
}



static inline void __client_stat_info_increase_session(client_stat_info_session_t *dst,
        const client_stat_info_session_t *inc)
{
    dst->idle      += inc->idle;
    dst->syn_send  += inc->syn_send;
    dst->establish += inc->establish;
    dst->fin_send  += inc->fin_send;
    dst->closed    += inc->closed;
}

void client_stat_info_increase(client_stat_info_t *dst,
        const client_stat_info_t *inc)
{
    __client_stat_info_increase_traffic(&dst->traffic, &inc->traffic);
    __client_stat_info_increase_latency(&dst->latency, &inc->latency);
    __client_stat_info_increase_session(&dst->session, &inc->session);
}

static inline void __client_stat_info_delta_traffic(client_stat_info_traffic_t *delta, 
        const client_stat_info_traffic_t *new, const client_stat_info_traffic_t *old)
{
    delta->rx_pkts      = new->rx_pkts - old->rx_pkts;
    delta->tx_pkts      = new->tx_pkts - old->tx_pkts;
    delta->tx_busy_pkts = new->tx_busy_pkts - old->tx_busy_pkts;
    delta->bug_pkts     = new->bug_pkts - old->bug_pkts;
}

static inline void __client_stat_info_delta_latency(client_stat_info_latency_t *delta, 
        const client_stat_info_latency_t *new, const client_stat_info_latency_t *old)
{
    uint16_t                    i;

    delta->total_us = new->total_us - old->total_us;

    for (i=0; i<CLIENT_STAT_LATENCY_NR; ++i) {
        delta->cnt_tbl[i] = new->cnt_tbl[i] - old->cnt_tbl[i];
    }
}

static inline void __client_stat_info_delta_session(client_stat_info_session_t *delta, 
        const client_stat_info_session_t *new, const client_stat_info_session_t *old)
{
    delta->idle      = new->idle - old->idle;
    delta->syn_send  = new->syn_send - old->syn_send;
    delta->establish = new->establish - old->establish;
    delta->fin_send  = new->fin_send - old->fin_send;
    delta->closed    = new->closed - old->closed;
}

void client_stat_info_delta(client_stat_info_t *delta, 
        const client_stat_info_t *new, const client_stat_info_t *old)
{
    __client_stat_info_delta_traffic(&delta->traffic, &new->traffic, &old->traffic);
    __client_stat_info_delta_latency(&delta->latency, &new->latency, &old->latency);
    __client_stat_info_delta_session(&delta->session, &new->session, &old->session);
}


