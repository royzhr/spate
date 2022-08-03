/*
 * Rodzhang
 *
 */

#include "host_garp.h"
#include "../host_mgr.h"
#include <spate_mm.h>
#include <spate_plane.h>
#include "garp_generate.h"


#define GARP_PKT_SIZE       512


void host_garp_announce(uint16_t worker_id)
{
    char                    *pkt;
    uint32_t                ip;
    uint16_t                pkt_len;
    uint16_t                i;

    if (!g_host->cfg.garp_enable) {
        return;
    }

    pkt = mm_vmalloc(GARP_PKT_SIZE);
    if (!pkt) {
        return;
    }

    for (i=0; i<g_host->cfg.host_ip.cnt; ++i) {
        ip = g_host->cfg.host_ip.addr + i;

        pkt_len = garp_generate_packet(pkt, GARP_PKT_SIZE, ip);

        __plane_netdev_tx_packet(g_plane->netdev, pkt, pkt_len, worker_id);
    }

    mm_vfree(pkt, GARP_PKT_SIZE);
}

