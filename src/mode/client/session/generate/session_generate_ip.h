/*
 * Rodzhang
 *
 */

#ifndef __SESSION_GENERATE_IP_H__
#define __SESSION_GENERATE_IP_H__


#include <spate_core.h>
#include <spate_net.h>
#include <spate_mode_client.h>
#include "session_generate_l4.h"
#include "session_generate_payload.h"
#include "../session.h"
#include <spate_utils.h>



static inline uint16_t __generate_iphdr_get_len_in_hdr(uint16_t l4_len, uint16_t payload_len)
{
    return sizeof(ipv4_hdr_t) + l4_len + payload_len;
}


static inline void __generate_iphdr_pro(client_instance_context_t *ctx, 
        ipv4_hdr_t *iphdr, session_engress_t *engress, uint16_t len_in_iphdr)
{
    iphdr->version_ihl      = 0x45;
    iphdr->type_of_service  = 0x0;
    iphdr->total_length     = htons(len_in_iphdr);
    iphdr->packet_id        = htons(++ctx->tc.packet_id);
    iphdr->fragment_offset  = 0x40;
    iphdr->time_to_live     = 0x40;
    iphdr->next_proto_id    = __generate_l4_get_proto(engress);

    iphdr->src_addr         = htonl(engress->sip);
    iphdr->dst_addr         = htonl(engress->dip);

    iphdr->hdr_checksum     = 0;
}


static inline void __generate_iphdr_post(ipv4_hdr_t *iphdr)
{
    iphdr->hdr_checksum = __np_ipv4_cksum(iphdr);
}

static inline uint16_t __generate_packet_ip_data_normal(client_instance_context_t *ctx,
        session_engress_t *engress, char *ip_data, uint64_t now)
{
    char                    *tail;
    ipv4_hdr_t              *iphdr;
    char                    *l4hdr;
    char                    *payload;
    uint16_t                l4_len, payload_len;

    iphdr       = (ipv4_hdr_t *)(ip_data);

    l4hdr       = (char *)(iphdr + 1);
    l4_len      = __generate_l4_get_len(engress);

    payload     = (char *)(l4hdr + l4_len);
    payload_len = __generate_payload_get_len();

    tail        = (char *)(payload + payload_len);

    generate_payload(payload, payload_len, engress, now);

    __generate_iphdr_pro(ctx, iphdr, engress, 
            __generate_iphdr_get_len_in_hdr(l4_len, payload_len));
    
    __generate_l4hdr(l4hdr, iphdr, payload_len, engress);

    __generate_iphdr_post(iphdr);

    return tail - ip_data;
}

static inline uint16_t __generate_packet_ip_data_tcp_special( client_instance_context_t *ctx,
        session_engress_t *engress, char *ip_data, uint32_t gen_code)
{
    ipv4_hdr_t              *iphdr;
    tcp_hdr_t               *tcp;

    ASSERT(engress->proto == SPATE_TCP);

    iphdr = (ipv4_hdr_t *)(ip_data);
    tcp   = (tcp_hdr_t *)(iphdr + 1);

    __generate_iphdr_pro(ctx, iphdr, engress, 
            __generate_iphdr_get_len_in_hdr(sizeof(*tcp), 0));
    
    generate_tcphdr_special(tcp, iphdr, 0, engress, gen_code);

    __generate_iphdr_post(iphdr);

    return sizeof(ipv4_hdr_t) + sizeof(tcp_hdr_t);
}

static inline uint16_t __generate_packet_ip_data(client_instance_context_t *ctx,
        session_engress_t *engress, char *ip_data, uint64_t now, uint32_t gen_code)
{
    switch (gen_code) {
        case SESSION_GEN_NORMAL:
            return __generate_packet_ip_data_normal(ctx, engress, ip_data, now);
            break;

        case SESSION_GEN_TCP_SYNACK_ACK:
        case SESSION_GEN_TCP_RST:
            return __generate_packet_ip_data_tcp_special(ctx, engress, ip_data, gen_code);
            break;
    }

    return 0;
}




#endif /* __SESSION_GENERATE_IP_H__ */
