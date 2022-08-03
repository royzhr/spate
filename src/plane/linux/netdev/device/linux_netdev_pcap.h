/*
 * Rodzhang
 *
 */

#ifndef __LINUX_NETDEV_PCAP_H__
#define __LINUX_NETDEV_PCAP_H__


#include <spate_core.h>
#include <spate_main.h>
#include <spate_pcap.h>
#include <spate_instance.h>
#include "../../plane_linux_netdev.h"
#include "../../../plane_utils.h"
#include <spate_utils.h>



static inline void __linux_netdev_pcap(char **pkts, uint16_t *lens, 
        uint16_t pkt_nr, int is_rx)
{
    uint16_t                i;
    pcap_file_t             *pcap_file;
    uint64_t                now;

    if (likely(!g_main->pcap_enable)) {
        return;
    }

    pcap_file = __get_instance_pcap_file();
    if (unlikely(!pcap_file)) {
        return;
    }

    now = __plane_get_cycles();

    for (i=0; i<pkt_nr; ++i) {
        if (__pcap_is_match(is_rx, pkts[i], lens[i])) {
            pcap_file->vptr->fsave(pcap_file, now, pkts[i], lens[i]);
        }
    }
}


#endif /* __LINUX_NETDEV_PCAP_H__ */
