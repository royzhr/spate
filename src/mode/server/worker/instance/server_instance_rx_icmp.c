/*
 * Rodzhang
 *
 */

#include "server_instance_rx_icmp.h"


int server_instance_rx_icmp(icmp_hdr_t *icmp, uint16_t len)
{
    if (!__spate_is_icmphdr_check_ok(icmp, len)) {
        return INSTANCE_RX_RET_DROP;
    }

    __spate_icmphdr_modify_to_replay(icmp);

    return INSTANCE_RX_RET_TX;
}
