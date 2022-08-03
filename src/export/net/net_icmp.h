/*
 * Rodzhang
 *
 */

#ifndef __NET_ICMP_H__
#define __NET_ICMP_H__

#include "net_proto/net_proto.h"


static __inline int __spate_is_icmphdr_check_ok(icmp_hdr_t *icmp, uint16_t len)
{
    if (len < sizeof(*icmp)) {
        return 0;
    }

    if (icmp->icmp_type != NP_IP_ICMP_ECHO_REQUEST) {
        return 0;
    }

    if (icmp->icmp_code != 0) {
        return 0;
    }

    return 1;
}

static __inline uint16_t __icmp_replay_checksum(icmp_hdr_t *icmp)
{
    uint32_t            cksum;

    cksum = ~icmp->icmp_cksum & 0xFFFF;
    cksum += ~__htons(NP_IP_ICMP_ECHO_REQUEST << 8) & 0xffff;
    cksum += __htons(NP_IP_ICMP_ECHO_REPLY << 8);
    cksum = (cksum & 0xffff) + (cksum >> 16);
    cksum = (cksum & 0xffff) + (cksum >> 16);

    return (uint16_t)~cksum;
}

static __inline void __spate_icmphdr_modify_to_replay(icmp_hdr_t *icmp)
{
    icmp->icmp_type = NP_IP_ICMP_ECHO_REPLY;

    icmp->icmp_cksum = __icmp_replay_checksum(icmp);
}





#endif /* __NET_ICMP_H__ */
