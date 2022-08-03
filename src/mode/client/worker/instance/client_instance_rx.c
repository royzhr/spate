/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_net.h>
#include <spate_drop.h>
#include <spate_vxlan.h>
#include <spate_session.h>
#include <spate_plane.h>
#include "client_instance_rx.h"
#include "client_instance_rx_ip.h"
#include "client_instance_rx_arp.h"
#include "client_instance_rx_vxlan.h"
#include "client_instance_stat.h"
#include <spate_utils.h>


static inline int __client_instance_on_recv_ip(eth_hdr_t *ethhdr, char *ip, 
        uint16_t len, client_instance_rx_param_t *rxp)
{
    if (__vxlan_is_enable()) {
        return client_instance_rx_vxlan(ethhdr, ip, len, rxp);
    } else {
        return __client_instance_rx_ip(ethhdr, (ipv4_hdr_t*)ip, len, rxp);
    }
}

static inline int __client_instance_on_recv_packet(client_instance_context_t *ctx, 
        char *pkt_data, uint16_t pkt_len, client_instance_rx_param_t *rxp)
{
    uint16_t                eth_len;
    uint16_t                ether_type;
    eth_hdr_t               *ethhdr;

    ethhdr   = (eth_hdr_t *)pkt_data;

    if (__spate_ethhdr_parse(ethhdr, pkt_len, &ether_type, &eth_len) < 0) {
        SPATE_DROP(DROP_ETHHDR_ERROR, ethhdr);
        return INSTANCE_RX_RET_DROP;
    }

    if (!__spate_is_ethhdr_dmac_myself(ethhdr, __spate_netdev_mac_addr())) {
        SPATE_DROP(DROP_ETH_DMAC_REJECT, ethhdr);
        return INSTANCE_RX_RET_DROP;
    }

    if (likely(ether_type == NP_ETHER_TYPE_IPV4)) {

        return __client_instance_on_recv_ip(ethhdr, pkt_data + eth_len, 
                pkt_len - eth_len, rxp);

    } else if (ether_type == NP_ETHER_TYPE_ARP) {

        return client_instance_rx_arp(ethhdr, (arp_hdr_t *)(pkt_data+eth_len), 
                pkt_len-eth_len);
    }

    SPATE_DROP(DROP_ETH_PROTO_REJECT, ethhdr);

    return INSTANCE_RX_RET_DROP;
}


int client_instance_on_recv_packet(client_instance_context_t *ctx, char *pkt_data, 
        uint16_t pkt_len, client_instance_rx_param_t *rxp)
{
    int                     ret;
    uint16_t                rebuild_len;

    rxp->need_session_generate  = 0;
    rxp->need_stat              = 0;
    memset(&rxp->rx_stat_param, 0, sizeof(rxp->rx_stat_param));
    
    ret = __client_instance_on_recv_packet(ctx, pkt_data, pkt_len, rxp);

    if (likely(rxp->need_stat)) {
        client_instance_stat_rx(ctx, &rxp->rx_stat_param);
    }

    if (unlikely(rxp->need_session_generate)) {
        ASSERT(ret == INSTANCE_RX_RET_DROP);

        if (g_session->ops->generate_pkt(ctx, rxp->now, 
                    &rxp->session_generate_ctrl, 
                    pkt_data, &rebuild_len) == 0) {

            rxp->pkt_data_len = rebuild_len;
            ret               = INSTANCE_RX_RET_TX;
        }

    }
    
    return ret;
}

