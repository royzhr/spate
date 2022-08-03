/*
 * Rodzhang
 *
 */

#ifndef __SESSION_GENERATE_TCP_H__
#define __SESSION_GENERATE_TCP_H__



#include <spate_core.h>
#include <spate_net.h>
#include "../session_mgr.h"


void generate_tcphdr(tcp_hdr_t *tcp, ipv4_hdr_t *iphdr, uint16_t payload_len, 
        session_engress_t *engress);

void generate_tcphdr_special(tcp_hdr_t *tcp, ipv4_hdr_t *iphdr, uint16_t payload_len,
        session_engress_t *engress, uint32_t gen_code);


#endif /* __SESSION_GENERATE_TCP_H__ */
