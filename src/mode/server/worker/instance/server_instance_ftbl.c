/*
 * Rodzhang
 *
 */

#include "server_instance_ftbl.h"
#include "server_instance_stat.h"

#include <spate_net.h>
#include <spate_plane.h>
#include "server_instance_rx_ip.h"
#include "server_instance_rx_arp.h"
#include "server_instance_rx_vxlan.h"


static inline int __server_instance_on_recv_ip(char *ip, uint16_t len)
{
    if (__is_server_vxlan_enable()) {
        return server_instance_rx_vxlan(ip, len);   
    } else {
        return __server_instance_rx_ip((ipv4_hdr_t*)ip, len);
    }
}

/*
 * Return Value:
 * 0    : drop
 * 1    : need to tx
 */
static int _server_instance_on_recv_packet(server_instance_context_t *my,
        char *pkt_data, uint16_t pkt_len)
{
    uint16_t                ether_type;
    uint16_t                eth_len;
    eth_hdr_t               *ethhdr;
    int                     ret;

    ret = INSTANCE_RX_RET_DROP;

    ethhdr = (eth_hdr_t *)pkt_data;

    if (__spate_ethhdr_parse(ethhdr, pkt_len, &ether_type, &eth_len) < 0) {
        return INSTANCE_RX_RET_DROP;
    }

    if (!__spate_is_ethhdr_dmac_myself(ethhdr, __spate_netdev_mac_addr())) {
        return INSTANCE_RX_RET_DROP;
    }

    if (ether_type == NP_ETHER_TYPE_IPV4) {

        ret = __server_instance_on_recv_ip(pkt_data+eth_len, pkt_len-eth_len);

    } else if (ether_type == NP_ETHER_TYPE_ARP) {

        ret = server_instance_rx_arp((arp_hdr_t *)(pkt_data+eth_len), pkt_len-eth_len);

    } else {
        return INSTANCE_RX_RET_DROP;
    }

    if (ret) {
        __spate_ethhdr_reverse_mac(ethhdr, __spate_netdev_mac_addr());
    }

    return ret;
}


const server_instance_ftbl_t c_server_instance_ftbl = {
    .on_recv_packet = _server_instance_on_recv_packet,
    .on_stat_inc    = server_instance_on_stat_inc,
    .on_stat_update = server_instance_on_stat_update,
};



