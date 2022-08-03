/*
 * Rodzhang
 *
 */

#ifndef __SESSION_GENERATE_L4_H__
#define __SESSION_GENERATE_L4_H__


#include <spate_core.h>
#include <spate_net.h>
#include "session_generate_udp.h"
#include "session_generate_tcp.h"
#include "../session.h"


static inline uint8_t __generate_l4_get_proto(session_engress_t *engress)
{
    return __spate_proto_to_ip_proto(engress->proto);
}

static inline uint16_t __generate_l4_get_len(session_engress_t *engress)
{
    if (engress->proto == SPATE_UDP) {
        return sizeof(udp_hdr_t);
    } else {
        return sizeof(tcp_hdr_t);
    }
}


static inline void __generate_l4hdr(void *l4hdr, ipv4_hdr_t *iphdr, 
        uint16_t payload_len, session_engress_t *engress)
{
    if (engress->proto == SPATE_UDP) {
        __generate_udphdr((udp_hdr_t *)l4hdr, iphdr, payload_len, engress);
    } else {
        generate_tcphdr((tcp_hdr_t *)l4hdr, iphdr, payload_len, engress); 
    }
}



#endif /* __SESSION_GENERATE_L4_H__ */
