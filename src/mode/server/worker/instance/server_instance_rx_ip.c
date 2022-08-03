/*
 * Rodzhang
 *
 */

#include "server_instance_rx_ip.h"
#include "server_instance_rx_icmp.h"
#include <spate_host.h>


static int __server_instance_rx_ip_icmp(ipv4_hdr_t *iphdr, uint16_t len)
{
    uint16_t                l4_len, iphdr_len;
    void                    *l4_hdr;

    if (!__host_is_icmp_enable()) {
        return INSTANCE_RX_RET_DROP;
    }

    if (!__host_is_my_ip(iphdr->dst_addr)) {
        return INSTANCE_RX_RET_DROP;
    }

    iphdr_len = __spate_iphdr_len(iphdr);
    l4_len = len - iphdr_len;
    l4_hdr = (char *)(iphdr) + iphdr_len;

    return server_instance_rx_icmp((icmp_hdr_t *)(l4_hdr), l4_len);
}


int server_instance_rx_ip_other(ipv4_hdr_t *iphdr, uint16_t len)
{
    if (iphdr->next_proto_id == IPPROTO_ICMP) {
        return __server_instance_rx_ip_icmp(iphdr, len);
    }

    return INSTANCE_RX_RET_DROP;
}

