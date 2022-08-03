/*
 * Rodzhang
 *
 */

#ifndef __DPDK_NETDEV_PCAP_H__
#define __DPDK_NETDEV_PCAP_H__

#include <spate_core.h>
#include <spate_main.h>
#include <spate_pcap.h>
#include <spate_instance.h>
#include "../../plane_dpdk_netdev.h"
#include "../../dpdk_inc.h"
#include "../../../plane_utils.h"
#include <spate_utils.h>


static inline void __dpdk_netdev_pcap(struct rte_mbuf **mbufs, uint16_t mbuf_len, int is_rx)
{
    pcap_file_t             *pcap_file;
    uint16_t                i;
    uint16_t                pkt_len;
    char                    *pkt_data;
    uint64_t                now;

    if (likely(!g_main->pcap_enable)) {
        return;
    }

    pcap_file = __get_instance_pcap_file();
    if (!pcap_file) {
        return;
    }

    for (i=0; i<mbuf_len; ++i) {
        DPDK_PACKET_MBUF(pkt_data, pkt_len, mbufs[i]);

        if (__pcap_is_match(is_rx, pkt_data, pkt_len)) {
            now = __plane_get_cycles();

            pcap_file->vptr->fsave(pcap_file, now, pkt_data, pkt_len);
        }
    }

}




#endif /* __DPDK_NETDEV_PCAP_H__ */
