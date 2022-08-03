/*
 * Rodzhang
 *
 */

#ifndef __SERVER_INSTANCE_RX_TCP_H__
#define __SERVER_INSTANCE_RX_TCP_H__


#include <spate_core.h>
#include <spate_net.h>
#include <spate_server_listen.h>
#include "server_instance_rx_payload.h"



static inline uint16_t __server_tcphdr_addack_cksum(tcp_hdr_t *tcp)
{
    uint16_t                cksum;

    if (tcp->cksum < 0x1000) {
        cksum =  tcp->cksum - 0x1000 - 1;
    } else {

        cksum =  tcp->cksum - 0x1000;
    }

    return cksum;
}


static inline void __server_tcphdr_update(tcp_hdr_t *tcp, ipv4_hdr_t *iphdr, uint16_t l4_len)
{
    uint16_t                tmp;

    memcpy(&tmp, &tcp->src_port, sizeof(uint16_t));
    memcpy(&tcp->src_port, &tcp->dst_port, sizeof(uint16_t));
    memcpy(&tcp->dst_port, &tmp, sizeof(uint16_t));

    if (tcp->tcp_flags & NP_TCP_ACK_FLAG) {
        return;
    }

    tcp->tcp_flags = tcp->tcp_flags | NP_TCP_ACK_FLAG;

    tcp->cksum = __server_tcphdr_addack_cksum(tcp);

    /*
    uint16_t old_cksum, new_cksum;

    old_cksum = tcp->cksum;
    new_cksum = __server_tcphdr_addack_cksum(tcp);

    tcp->cksum = 0;
    tcp->cksum = __np_ipv4_udptcp_cksum(iphdr, (const void *)tcp, l4_len);

    if (tcp->cksum != new_cksum) {
        LOGE("old:%x,new:%x,right:%x, %x->%x", old_cksum, new_cksum, tcp->cksum, 
                ntohs(old_cksum), ntohs(tcp->cksum));
        ASSERT(0);
    }
    */
    
}


static inline int __server_instance_rx_tcp(tcp_hdr_t *tcp, uint16_t len, ipv4_hdr_t *iphdr)
{
    spate_payload_t         *ps;
    uint16_t                tcphdr_len, payload_len;
    int                     ret;


    if (unlikely(!__spate_is_tcphdr_check_ok(tcp, len))) {
        return INSTANCE_RX_RET_DROP;
    }

    if (unlikely(!__is_server_listen_port(tcp->dst_port))) {
        //LOGD("not tcp listen port:%u", ntohs(tcp->dst_port));
        return INSTANCE_RX_RET_DROP;
    }

    tcphdr_len  = __spate_tcphdr_len(tcp);
    ps          = (spate_payload_t *)((char *)tcp + tcphdr_len);

    if (unlikely(len < tcphdr_len)) {
        return INSTANCE_RX_RET_DROP;
    }

    payload_len = len - tcphdr_len;
    
    ret = __server_instance_rx_payload(ps, payload_len);
    
    if (likely(ret)) {
        __server_tcphdr_update(tcp, iphdr, len);
    }

    return ret;
}





#endif /* __SERVER_INSTANCE_RX_TCP_H__ */
