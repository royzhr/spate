/*
 * Rodzhang
 *
 */

#include "server_instance_rx_vxlan.h"


static inline int __server_instance_vxlan_overlay(char *overlay, uint16_t overlay_len)
{
    uint16_t                ether_type;
    uint16_t                eth_len;
    eth_hdr_t               *ethhdr;
    int                     ret;

    ret = INSTANCE_RX_RET_DROP;

    ethhdr = (eth_hdr_t *)overlay;

    if (__spate_ethhdr_parse(ethhdr, overlay_len, &ether_type, &eth_len) < 0) {
        return INSTANCE_RX_RET_DROP;
    }

    /*
     * For overlay, there is no need to check whether dmac is its own nic-address
     */

    if (ether_type == NP_ETHER_TYPE_IPV4) {

        ret = __server_instance_rx_ip((ipv4_hdr_t *)(overlay+eth_len), overlay_len-eth_len);

    } else {
        return INSTANCE_RX_RET_DROP;
    }

    if (ret) {
        __spate_ethhdr_reverse_mac(ethhdr, __spate_netdev_mac_addr());
    }

    return ret;
}

static inline int __server_instance_vxlan_underlay(char *underlay, uint16_t underlay_len)
{
    ipv4_hdr_t          *iphdr;
    
    iphdr = (ipv4_hdr_t *)(underlay);

    /*
     * For vxlan underpay, udp dst port is always 4789.
     */
    __spate_iphdr_reverse_ip(iphdr);

    return INSTANCE_RX_RET_TX;
}

static inline int __is_server_vxlan_packet(spate_vxlan_underlay_info_t *ui)
{
    return __spate_cfg_ip_is_contain(&g_server_listen->cfg.vxlan_vtep_ip, ui->underlay_dip);
}

int server_instance_rx_vxlan(char *data, uint16_t len)
{
    spate_vxlan_underlay_info_t     ui;
    uint16_t                        underlay_len;
    uint16_t                        overlay_len;
    char                            *underlay;
    char                            *overlay;

    underlay = data;

    if (__spate_vxlan_underlay_info(&ui, underlay, len) < 0) {
        /*
         * Not underlay
         */
        goto not_vxlan_packet;
    }

    underlay_len = ui.underlay_len;
    overlay      = underlay + underlay_len;
    overlay_len  = len - underlay_len;

    if (!__is_server_vxlan_packet(&ui)) {
        goto not_vxlan_packet;
    }

    if (!__server_instance_vxlan_overlay(overlay, overlay_len)) {
        return INSTANCE_RX_RET_DROP;
    }

    return __server_instance_vxlan_underlay(underlay, underlay_len);

not_vxlan_packet:
    return __server_instance_rx_ip((ipv4_hdr_t*)underlay, len);
}
