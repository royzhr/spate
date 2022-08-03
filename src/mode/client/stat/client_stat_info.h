/*
 * Rodzhang
 *
 */

#ifndef __CLIENT_STAT_INFO_H__
#define __CLIENT_STAT_INFO_H__


#include <spate_stat.h>
#include "../../../export/client/spate_client_stat.h"


typedef struct {
    
    uint32_t                idle;
    uint32_t                syn_send;
    uint32_t                establish;
    uint32_t                fin_send;
    uint32_t                closed;

} client_stat_info_session_t;



typedef struct {

    client_stat_info_traffic_t      traffic;

    client_stat_info_latency_t      latency;

    client_stat_info_session_t      session;

} client_stat_info_t;


void client_stat_info_zero(client_stat_info_t *cs);

void client_stat_info_copy(client_stat_info_t *dst, 
        const client_stat_info_t *src);

void client_stat_info_increase(client_stat_info_t *dst,
        const client_stat_info_t *inc);

void client_stat_info_delta(client_stat_info_t *delta, 
        const client_stat_info_t *new, const client_stat_info_t *old);


#endif /* __CLIENT_STAT_INFO_H__ */
