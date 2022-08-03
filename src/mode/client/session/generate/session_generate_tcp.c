/*
 * Rodzhang
 *
 */

#include <spate_utils.h>
#include <spate_net.h>
#include "session_generate_tcp.h"

static inline void __generate_tcphdr_comm(tcp_hdr_t *tcp, session_engress_t *engress)
{
    tcp->src_port = htons(engress->sport);
    tcp->dst_port = htons(engress->dport);
    tcp->sent_seq = htonl(engress->sequence);
    tcp->recv_ack = htonl(engress->sequence);
    tcp->data_off = (sizeof(tcp_hdr_t)/sizeof(uint32_t)) << 4;

    tcp->rx_win   = htons(8192);
    tcp->tcp_urp  = 0;
    tcp->cksum    = 0;
}


void generate_tcphdr(tcp_hdr_t *tcp, ipv4_hdr_t *iphdr, uint16_t payload_len, 
        session_engress_t *engress)
{
    uint16_t                seq_add;

    seq_add = 0;

    __generate_tcphdr_comm(tcp, engress);

    if (engress->state == ST_SYN_SEND) {
        seq_add += 1;

        tcp->tcp_flags = NP_TCP_SYN_FLAG;
    } else if (engress->state == ST_FIN_SEND) {
        seq_add += 1;

        tcp->tcp_flags = NP_TCP_FIN_FLAG;
    } else {
        ASSERT(engress->state == ST_ESTABLISH);

        tcp->tcp_flags = NP_TCP_ACK_FLAG;
    }

    /*
     * check sum
     */
    tcp->cksum = __np_ipv4_udptcp_cksum(iphdr, (const void *)tcp, sizeof(tcp_hdr_t)+payload_len);

    seq_add += payload_len;
    
    if (!engress->retrans) {
        engress->sequence += seq_add;
    }
    
}

void generate_tcphdr_special(tcp_hdr_t *tcp, ipv4_hdr_t *iphdr, uint16_t payload_len,
        session_engress_t *engress, uint32_t gen_code)
{
    //ASSERT(gen_code == SESSION_GEN_TCP_SYNACK_ACK);

    __generate_tcphdr_comm(tcp, engress);
    
    switch (gen_code) {
        case SESSION_GEN_TCP_SYNACK_ACK:
            tcp->tcp_flags = NP_TCP_ACK_FLAG;
            break;

        case SESSION_GEN_TCP_RST:
            tcp->tcp_flags = NP_TCP_RST_FLAG;
            break;

        default:
            break;
    }

    tcp->cksum = __np_ipv4_udptcp_cksum(iphdr, (const void *)tcp, sizeof(tcp_hdr_t)+payload_len);
}


