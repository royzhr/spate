/*
 * Rodzhang
 *
 */

#include <spate_vxlan.h>
#include <spate_session.h>
#include "client_instance_rx_vxlan.h"


static inline void __client_instance_vxlan_overlay_check_underlay(ipv4_hdr_t *overlay_iphdr, 
        client_instance_rx_param_t *rxp, spate_vxlan_underlay_info_t *ui)
{

    uint32_t                odip;
    uint32_t                osip;

    odip = ntohl(overlay_iphdr->dst_addr);
    osip = ntohl(overlay_iphdr->src_addr);

    if (!__spate_cfg_ip_is_contain_on_host(&g_session->cfg.sip, odip)) {
        goto vxlan_underlay_ip_bug;
    }
    if (!__spate_cfg_ip_is_contain_on_host(&g_session->cfg.dip, osip)) {
        goto vxlan_underlay_ip_bug;
    }

    if (g_vxlan->ops->underlay_sip_get(odip) != ntohl(ui->underlay_dip)) {
        goto vxlan_underlay_ip_bug;
    }
    if (g_vxlan->ops->underlay_dip_get(osip) != ntohl(ui->underlay_sip)) {
        goto vxlan_underlay_ip_bug;
    }

    return;

vxlan_underlay_ip_bug:
    rxp->rx_stat_param.bug_code = CLIENT_RX_STAT_BUG_CODE_VXLAN;
}


static inline int __client_instance_vxlan_overlay_ip(ipv4_hdr_t *iphdr, uint16_t len, 
        client_instance_rx_param_t *rxp)
{
    uint16_t                l4_len, iphdr_len;
    void                    *l4_hdr;

    if (unlikely(!__spate_is_iphdr_check_ok(iphdr, len))) {
        SPATE_DROP(DROP_IPHDR_ERROR, iphdr);
        return INSTANCE_RX_RET_DROP;
    }

    iphdr_len = __spate_iphdr_len(iphdr);
    l4_len    = len - iphdr_len;
    l4_hdr    = (char *)(iphdr) + iphdr_len;

    if (iphdr->next_proto_id == IPPROTO_UDP) {
        return __client_instance_rx_udp((udp_hdr_t *)(l4_hdr), l4_len, rxp);

    } else if (iphdr->next_proto_id == IPPROTO_TCP) {
        return __client_instance_rx_tcp((tcp_hdr_t *)(l4_hdr), l4_len, rxp, iphdr);
    }

    SPATE_DROP(DROP_IP_PROTO_REJECT, iphdr);
    return INSTANCE_RX_RET_DROP;
}

static inline int __client_instance_vxlan_overlay(char *overlay, uint16_t overlay_len, 
        client_instance_rx_param_t *rxp, spate_vxlan_underlay_info_t *ui)
{
    uint16_t                eth_len;
    uint16_t                ether_type;
    eth_hdr_t               *ethhdr;

    ethhdr   = (eth_hdr_t *)overlay;

    if (__spate_ethhdr_parse(ethhdr, overlay_len, &ether_type, &eth_len) < 0) {
        SPATE_DROP(DROP_ETHHDR_ERROR, ethhdr);
        return INSTANCE_RX_RET_DROP;
    }

    /*
     * For overlay, there is no need to check whether dmac is its own nic-address
     */

    if (likely(ether_type == NP_ETHER_TYPE_IPV4)) {

        ipv4_hdr_t          *iphdr;
        uint16_t            ip_len;
        int                 ret;

        iphdr  = (ipv4_hdr_t *)(overlay + eth_len);
        ip_len = overlay_len - eth_len;

        ret = __client_instance_vxlan_overlay_ip(iphdr, ip_len, rxp);

        if (rxp->need_stat) {
            __client_instance_vxlan_overlay_check_underlay(iphdr, rxp, ui);
        }

        return ret;
    }

    SPATE_DROP(DROP_ETH_PROTO_REJECT, ethhdr);

    return INSTANCE_RX_RET_DROP;
}

static inline int __is_client_vxlan_packet(spate_vxlan_underlay_info_t *ui)
{
    if (!__spate_cfg_ip_is_contain(&g_vxlan->cfg.underlay_sip, ui->underlay_dip)) {
        return 0;
    }

    if (!__spate_cfg_ip_is_contain(&g_vxlan->cfg.underlay_dip, ui->underlay_sip)) {
        return 0;
    }

    return 1;
}

int client_instance_rx_vxlan(eth_hdr_t *ethhdr, char *ip, 
        uint16_t len, client_instance_rx_param_t *rxp)
{
    spate_vxlan_underlay_info_t     ui;
    uint16_t                        underlay_len;
    uint16_t                        overlay_len;
    char                            *underlay;
    char                            *overlay;

    underlay = ip;

    if (__spate_vxlan_underlay_info(&ui, underlay, len) < 0) {
        /*
         * Not underlay
         */
        goto not_vxlan_packet;
    }

    if (!__is_client_vxlan_packet(&ui)) {
        return INSTANCE_RX_RET_DROP;
    }

    underlay_len = ui.underlay_len;
    overlay      = underlay + underlay_len;
    overlay_len  = len - underlay_len;

    return __client_instance_vxlan_overlay(overlay, overlay_len, rxp, &ui);

not_vxlan_packet:
    return __client_instance_rx_ip(ethhdr, (ipv4_hdr_t*)ip, len, rxp);
}
