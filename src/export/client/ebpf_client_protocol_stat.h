/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_CLIENT_PROTOCOL_STAT_H__
#define __EBPF_CLIENT_PROTOCOL_STAT_H__


#include "spate_client_stat.h"



typedef struct {

    client_stat_info_traffic_t      traffic;
    client_stat_info_latency_t      latency;

} spate_ebpf_client_stat_t;


#endif /* __EBPF_CLIENT_PROTOCOL_STAT_H__ */
