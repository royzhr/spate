/*
 * Rodzhang
 *
 */

#include <stdio.h>
#include "linux_filter_mode.h"

#include <spate_host.h>
/*
 * Client Mode:
 */
#include <spate_session.h>
#include <spate_vxlan.h>




int build_filter_string_mode_client(char *str, uint16_t len)
{
    const session_cfg_t     *session_cfg;
    const vxlan_cfg_t       *vxlan_cfg;
    const host_cfg_t        *host_cfg;
    char                    *p;
    int                     is_first;
    uint16_t                port_min, port_max;

    session_cfg = &g_session->cfg;
    vxlan_cfg   = &g_vxlan->cfg;
    host_cfg    = &g_host->cfg;

    p           = str;
    is_first    = 1;

    if (host_cfg->arp_enable) {
        FILTER_STRING_PRE(is_first, p);
        p += sprintf(p, "arp ");
    }

    if (host_cfg->icmp_enable) {
        FILTER_STRING_PRE(is_first, p);
        p += sprintf(p, "icmp ");
    }

    if (vxlan_cfg->enable) {
        FILTER_STRING_PRE(is_first, p);
        p += sprintf(p, "udp dst port 4789 ");
        return 0;
    }

    /*
     * On receiving packets, the dst port of the packet is the source port in the configuration
     */
    port_min = session_cfg->sport.port;
    port_max = port_min + session_cfg->sport.cnt - 1;

    if (session_cfg->proto == SPATE_UDP) {
        
        FILTER_STRING_PRE(is_first, p);
        p += sprintf(p, "udp dst portrange %u-%u ", port_min, port_max);

    } else if (session_cfg->proto == SPATE_TCP) {
    
        FILTER_STRING_PRE(is_first, p);
        p += sprintf(p, "tcp dst portrange %u-%u ", port_min, port_max);
    }

    return 0;
}

