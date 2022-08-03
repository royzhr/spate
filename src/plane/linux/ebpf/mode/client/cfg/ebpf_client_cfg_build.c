/*
 *  Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_host.h>
#include <spate_session.h>
#include <spate_packet.h>
#include <spate_vxlan.h>
#include "../../../../plane_linux_utils.h"
#include "ebpf_client_cfg_build.h"



static void _ebpf_offload_client_config_build_session(spate_ebpf_session_config_t *session)
{
    session->sip = g_session->cfg.sip;
    session->dip = g_session->cfg.dip;
    session->sport = g_session->cfg.sport;
    session->dport = g_session->cfg.dport;

    session->proto = __spate_proto_to_ip_proto(g_session->cfg.proto);

}

static void _ebpf_offload_client_config_build_packet(spate_ebpf_packet_config_t *packet)
{
    packet->payload_size = g_packet->cfg.payload_size;
    packet->vlan_enable = g_packet->cfg.vlan_enable;
    packet->vlan_id = g_packet->cfg.vlan_id;

    memcpy(packet->dmac, g_packet->cfg.dmac, 6);
}

static void _ebpf_offload_client_config_build_vxlan(spate_ebpf_client_vxlan_config_t *vxlan)
{
    vxlan->vxlan_enable = g_vxlan->cfg.enable;
    vxlan->vni = g_vxlan->cfg.vni;
    vxlan->underlay_sip = g_vxlan->cfg.underlay_sip;
    vxlan->underlay_dip = g_vxlan->cfg.underlay_dip;
    vxlan->underlay_sport = g_vxlan->cfg.underlay_sport;

    memcpy(vxlan->overlay_smac, g_vxlan->cfg.overlay_smac, 6);
    memcpy(vxlan->underlay_dmac, g_vxlan->cfg.underlay_dmac, 6);
}

static void _ebpf_offload_client_config_build_host(spate_ebpf_host_config_t *host)
{
    host->icmp_enable = g_host->cfg.icmp_enable;
    host->arp_enable = g_host->cfg.arp_enable;
    host->host_ip = g_host->cfg.host_ip;
}

static void _ebpf_offload_client_config_build_netdev(spate_ebpf_net_device_config_t *netdev)
{
    plane_linux_netdev_t            *lix_dev;

    lix_dev = __get_plane_linux_netdev();

    netdev->ifindex = lix_dev->if_index;
    memcpy(netdev->mac_addr, lix_dev->base.info.mac_addr, 6);
}

int ebpf_offload_client_config_build(spate_ebpf_client_config_t *cfg)
{

    _ebpf_offload_client_config_build_session(&cfg->session);
    _ebpf_offload_client_config_build_packet(&cfg->packet);
    _ebpf_offload_client_config_build_vxlan(&cfg->vxlan);
    _ebpf_offload_client_config_build_host(&cfg->host);
    _ebpf_offload_client_config_build_netdev(&cfg->device);

    return 0;
}

