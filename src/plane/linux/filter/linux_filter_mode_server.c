/*
 * Rodzhang
 *
 */

#include "linux_filter_mode.h"

#include <spate_host.h>
/*
 * Server Mode:
 */
#include <spate_server_listen.h>



int build_filter_string_mode_server(char *str, uint16_t len)
{
    const server_listen_cfg_t   *listen_cfg;
    const host_cfg_t            *host_cfg;
    char                    *p;
    int                     is_first, has_udp;
    uint16_t                port_min, port_max;

    listen_cfg = &g_server_listen->cfg;
    host_cfg   = &g_host->cfg;

    p          = str;
    is_first   = 1;
    has_udp    = 0;

    if (host_cfg->arp_enable) {
        FILTER_STRING_PRE(is_first, p);
        p += sprintf(p, "arp ");
    }

    if (host_cfg->icmp_enable) {
        FILTER_STRING_PRE(is_first, p);
        p += sprintf(p, "icmp ");
    }

    port_min = listen_cfg->listen_port.port;
    port_max = port_min + listen_cfg->listen_port.cnt - 1;
    
    if (listen_cfg->listen_proto_mask & SPATE_TCP) {
        FILTER_STRING_PRE(is_first, p);
        p += sprintf(p, "tcp dst portrange %u-%u ", port_min, port_max);
    }

    if (listen_cfg->listen_proto_mask & SPATE_UDP) {
        has_udp = 1;
        FILTER_STRING_PRE(is_first, p);
        p += sprintf(p, "udp dst portrange %u-%u ", port_min, port_max);
    }

    if (listen_cfg->vxlan_enable) {
        if (has_udp && port_min<=4789 && port_max>=4789) {
        } else {
            FILTER_STRING_PRE(is_first, p);
            p += sprintf(p, "udp dst port 4789 ");
        }
    }

    return 0;
}


