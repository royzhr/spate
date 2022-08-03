/*
 *  Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_host.h>
#include <spate_server_listen.h>
#include "ebpf_server_cfg_build.h"
#include "../../../../plane_linux_utils.h"




int ebpf_offload_server_config_build(spate_ebpf_server_config_t *cfg)
{

    plane_linux_netdev_t            *dev;

    dev = __get_plane_linux_netdev();

    cfg->listen.listen_ip   = g_server_listen->cfg.listen_ip;
    cfg->listen.listen_port = g_server_listen->cfg.listen_port;
    if (g_server_listen->cfg.listen_proto_mask & SPATE_TCP) {
        cfg->listen.proto_tcp = 1;
    }
    if (g_server_listen->cfg.listen_proto_mask & SPATE_UDP) {
        cfg->listen.proto_udp = 1;
    }


    cfg->vxlan.vxlan_enable = g_server_listen->cfg.vxlan_enable;
    cfg->vxlan.vtep_ip      = g_server_listen->cfg.vxlan_vtep_ip;

    
    cfg->host.arp_enable  = g_host->cfg.arp_enable;
    cfg->host.icmp_enable = g_host->cfg.icmp_enable;
    cfg->host.host_ip     = g_host->cfg.host_ip;


    cfg->device.ifindex = dev->if_index;
    memcpy(cfg->device.mac_addr, dev->base.info.mac_addr, 6);

    return 0;
}

