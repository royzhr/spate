/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_packet.h>
#include <spate_net.h>
#include <spate_vxlan.h>
#include "session_generate_vxlan.h"
#include "session_generate_eth.h"
#include "session_generate_ip.h"
#include "session_generate_l4.h"
#include "session_generate_payload.h"
#include <spate_utils.h>


static inline uint16_t __vxlan_underlay_sport_get(client_instance_context_t *ctx)
{
    uint16_t                r;

    r = ctx->session_roll.sess_idx_curr % g_vxlan->cfg.underlay_sport.cnt;

    return g_vxlan->cfg.underlay_sport.port + r;
}

static inline uint32_t __vxlan_underlay_sip_get(session_engress_t *engress)
{
    return g_vxlan->ops->underlay_sip_get(engress->sip);
}

static inline uint32_t __vxlan_underlay_dip_get(session_engress_t *engress)
{
    return g_vxlan->ops->underlay_dip_get(engress->dip);
}


static uint16_t _generate_vxlan_underlay_len(void)
{
    uint16_t                eth_len;

    eth_len = __generate_ethhdr_get_len();

    return eth_len + sizeof(ipv4_hdr_t) + sizeof(udp_hdr_t) + sizeof(vxlan_hdr_t);
}

static inline void __generate_vxlan_underlay_vxlan_hdr(vxlan_hdr_t *vxlan)
{
    vxlan->vx_flags = htonl(0x08000000);
    vxlan->vx_vni   = htonl(g_vxlan->cfg.vni << 8);
}

static inline void __generate_vxlan_underlay_udp_hdr(client_instance_context_t *ctx,
        udp_hdr_t *udp, ipv4_hdr_t *iphdr, uint16_t overlay_len)
{
    uint16_t                len;
    uint16_t                sport;

    sport = __vxlan_underlay_sport_get(ctx);
    len   = sizeof(udp_hdr_t) + sizeof(vxlan_hdr_t) + overlay_len;

    udp->src_port    = htons(sport);
    udp->dst_port    = htons(4789);
    udp->dgram_len   = htons(len);
    udp->dgram_cksum = 0;
    udp->dgram_cksum = __np_ipv4_udptcp_cksum(iphdr, (const void *)udp, len);
}

static inline void __generate_vxlan_underlay_ip_hdr_pro(client_instance_context_t *ctx,
        session_engress_t *engress, ipv4_hdr_t *iphdr, uint16_t overlay_len)
{
    uint16_t                total_length;
    uint32_t                underlay_sip, underlay_dip;

    total_length = sizeof(ipv4_hdr_t) + sizeof(udp_hdr_t) + sizeof(vxlan_hdr_t) + overlay_len;
    underlay_sip = __vxlan_underlay_sip_get(engress);
    underlay_dip = __vxlan_underlay_dip_get(engress);

    iphdr->version_ihl      = 0x45;
    iphdr->type_of_service  = 0x0;
    iphdr->total_length     = htons(total_length);
    iphdr->packet_id        = htons(ctx->tc.packet_id);
    iphdr->fragment_offset  = 0x40;
    iphdr->time_to_live     = 0x40;
    iphdr->next_proto_id    = IPPROTO_UDP;

    iphdr->src_addr         = htonl(underlay_sip);
    iphdr->dst_addr         = htonl(underlay_dip);

    iphdr->hdr_checksum     = 0;
}

static inline void __generate_vxlan_underlay_ip_hdr_post(ipv4_hdr_t *iphdr)
{
    iphdr->hdr_checksum = __np_ipv4_cksum(iphdr);
}

static void _generate_vxlan_underlay(client_instance_context_t *ctx, 
        session_engress_t *engress, char *underlay, uint16_t overlay_len)
{
    eth_hdr_t               *ethhdr;
    ipv4_hdr_t              *iphdr;
    udp_hdr_t               *udp;
    vxlan_hdr_t             *vxlan;
    uint16_t                eth_len;

    ethhdr  = (eth_hdr_t *)underlay;
    eth_len = __generate_ethhdr_get_len();

    iphdr   = (ipv4_hdr_t *)((char*)ethhdr + eth_len);
    udp     = (udp_hdr_t *)(iphdr + 1);
    vxlan   = (vxlan_hdr_t *)(udp + 1);

    __generate_vxlan_underlay_vxlan_hdr(vxlan);

    __generate_vxlan_underlay_ip_hdr_pro(ctx, engress, iphdr, overlay_len);

    __generate_vxlan_underlay_udp_hdr(ctx, udp, iphdr, overlay_len);

    __generate_vxlan_underlay_ip_hdr_post(iphdr);

    __generate_ethhdr(ethhdr, eth_len, __vxlan_underlay_dmac_addr_get());
}

static inline void __generate_vxlan_overlay_ethhdr(eth_hdr_t *eth)
{
    if (g_vxlan->cfg.overlay_smac_is_setting) {
        memcpy(eth->s_addr, g_vxlan->cfg.overlay_smac, NP_ETH_ALEN);
    } else {
        memcpy(eth->s_addr, __spate_netdev_mac_addr(), NP_ETH_ALEN);
    }

    memcpy(eth->d_addr, __packet_dmac_addr_get(), NP_ETH_ALEN);

    eth->ether_type = htons(NP_ETHER_TYPE_IPV4);
}


static uint16_t _generate_vxlan_overlay(client_instance_context_t *ctx,
        session_engress_t *engress, char *overlay, uint64_t now, uint32_t gen_code)
{
    char                    *ip_data;
    eth_hdr_t               *ethhdr;
    uint16_t                eth_len, ip_len;

    ethhdr  = (eth_hdr_t *)(overlay);
    eth_len = sizeof(*ethhdr);

    ip_data = (char *)ethhdr + eth_len;

    ip_len  = __generate_packet_ip_data(ctx, engress, ip_data, now, gen_code);

    __generate_vxlan_overlay_ethhdr(ethhdr);

    return eth_len + ip_len;
}

uint16_t generate_vxlan_packet_data(client_instance_context_t *ctx, 
        session_engress_t * engress, char *pkt_data, uint64_t now, uint32_t gen_code)
{
    uint16_t                underlay_len;
    uint16_t                overlay_len;
    char                    *underlay, *overlay;

    underlay_len = _generate_vxlan_underlay_len();

    underlay = (char *)(pkt_data);
    overlay  = (char *)(underlay + underlay_len);

    overlay_len = _generate_vxlan_overlay(ctx, engress, overlay, now, gen_code);

    _generate_vxlan_underlay(ctx, engress, underlay, overlay_len);

    //LOGW("underlay_len %u, overlay_len: %u", underlay_len, overlay_len);

    return underlay_len + overlay_len;
}


