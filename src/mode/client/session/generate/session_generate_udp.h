/*
 * Rodzhang
 *
 */

#ifndef __SESSION_GENERATE_UDP_H__
#define __SESSION_GENERATE_UDP_H__


#include <spate_core.h>
#include <spate_net.h>
#include "../session_mgr.h"



static inline void __generate_udphdr(udp_hdr_t *udp, ipv4_hdr_t *iphdr, 
        uint16_t payload_len, session_engress_t *engress)
{
    udp->src_port    = htons(engress->sport);
    udp->dst_port    = htons(engress->dport);
    udp->dgram_len   = htons(payload_len+sizeof(*udp));
    udp->dgram_cksum = 0;
    udp->dgram_cksum = __np_ipv4_udptcp_cksum(iphdr, (const void *)udp, 
            sizeof(udp_hdr_t)+payload_len);
}

#endif /* __SESSION_GENERATE_UDP_H__ */
