/*
 * Rodzhang
 *
 */

#ifndef __CLIENT_INSTANCE_RX_TCP_H__
#define __CLIENT_INSTANCE_RX_TCP_H__


#include <spate_core.h>
#include <spate_net.h>
#include <spate_drop.h>
#include <spate_session.h>
#include <spate_fack_tcp.h>
#include "client_instance_rx_payload.h"




static inline void __client_instance_rx_tcp_flags(tcp_hdr_t *tcp, 
        spate_payload_t *ps, client_instance_rx_param_t *rxp)
{
    uint32_t                sess_idx;

    if (tcp->tcp_flags & (NP_TCP_SYN_FLAG|NP_TCP_FIN_FLAG)) {

        memcpy(&sess_idx, &ps->sess_index, sizeof(uint32_t));
        
        g_session->ops->on_tcp_update(sess_idx, tcp);

        /*
         * Do you need to reply ack to synack.
         */
        if ((tcp->tcp_flags & NP_TCP_SYN_FLAG) && g_fack_tcp->cfg.synack_ack_enable) {
            rxp->need_session_generate               = 1;
            rxp->session_generate_ctrl.sess_index    = sess_idx;
            rxp->session_generate_ctrl.generate_code = SESSION_GEN_TCP_SYNACK_ACK;
        }
    }
}

static inline int __client_instance_rx_tcp(tcp_hdr_t *tcp, uint16_t len, 
        client_instance_rx_param_t *rxp, ipv4_hdr_t *iphdr)
{
    spate_payload_t         *ps;
    int                     ret;
    uint16_t                tcphdr_len, payload_len;

    if (unlikely(!__spate_is_tcphdr_check_ok(tcp, len))) {
        SPATE_DROP(DROP_TCPHDR_ERROR, tcp);
        return INSTANCE_RX_RET_DROP;
    }

    if (unlikely(tcp->tcp_flags & NP_TCP_RST_FLAG)) {
        g_session->ops->on_recv_tcp_rst(iphdr, tcp);
        return INSTANCE_RX_RET_DROP;
    }

    tcphdr_len  = __spate_tcphdr_len(tcp);
    ps          = (spate_payload_t *)((char *)tcp + tcphdr_len);

    if (unlikely(len < tcphdr_len)) {
        SPATE_DROP(DROP_TCPHDR_ERROR, tcp);
        return INSTANCE_RX_RET_DROP;
    }

    payload_len = len - tcphdr_len;

    if (unlikely(!(tcp->tcp_flags & NP_TCP_ACK_FLAG))) {
        SPATE_DROP(DROP_TCP_NOACK, tcp);
        return INSTANCE_RX_RET_DROP;
    }

    ret = __client_instance_rx_payload(ps, payload_len, rxp);

    if (rxp->need_stat) {
        __client_instance_rx_tcp_flags(tcp, ps, rxp);
    }

    return ret;
}




#endif /* __CLIENT_INSTANCE_RX_TCP_H__ */
