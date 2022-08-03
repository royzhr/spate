/*
 * Rodzhang
 *
 */

#include "../host_mgr.h"
#include <spate_net.h>
#include <spate_plane.h>
#include "garp_generate.h"


static inline void __garp_generate_ethhdr(eth_hdr_t *eth)
{
    vlan_hdr_t          *vlan;

    memset(eth->d_addr, 0xff, NP_ETH_ALEN);
    memcpy(eth->s_addr, __spate_netdev_mac_addr(), NP_ETH_ALEN);

    if (g_host->cfg.garp_vlan_enable) {

        vlan = (vlan_hdr_t *)(eth + 1);

        eth->ether_type = htons(NP_ETHER_TYPE_VLAN);
        vlan->vlan_tci  = htons(g_host->cfg.garp_vlan_id);
        vlan->eth_proto = htons(NP_ETHER_TYPE_ARP);

    } else {

        eth->ether_type = htons(NP_ETHER_TYPE_ARP);
    }
}

static inline void __garp_generate_arphdr(arp_hdr_t *arp, uint32_t ip)
{
    arp->arp_hardware = htons(NP_ARP_HRD_ETHER);
    arp->arp_protocol = htons(NP_ETHER_TYPE_IPV4);
    arp->arp_hlen     = 6;
    arp->arp_plen     = 4;
    arp->arp_opcode   = htons(NP_ARP_OP_REQUEST);
    
    memcpy(arp->arp_data.arp_sha, __spate_netdev_mac_addr(), NP_ETH_ALEN);
    memset(arp->arp_data.arp_tha, 0, NP_ETH_ALEN);

    arp->arp_data.arp_sip = htonl(ip);
    arp->arp_data.arp_tip = htonl(ip);
}

static inline uint16_t __garp_ethhdr_len(void)
{
    if (g_host->cfg.garp_vlan_enable) {
        return sizeof(eth_hdr_t) + sizeof(vlan_hdr_t);
    } else {
        return sizeof(eth_hdr_t);
    }
}

uint16_t garp_generate_packet(char *pkt, uint16_t size, uint32_t ip)
{
    eth_hdr_t               *ethhdr;
    arp_hdr_t               *arp;
    uint16_t                ethhdr_len;

    ethhdr_len = __garp_ethhdr_len();

    ethhdr = (eth_hdr_t *)pkt;

    arp    = (arp_hdr_t *)((char*)ethhdr + ethhdr_len);

    __garp_generate_ethhdr(ethhdr);

    __garp_generate_arphdr(arp, ip);

    return ethhdr_len + sizeof(*arp);
}


