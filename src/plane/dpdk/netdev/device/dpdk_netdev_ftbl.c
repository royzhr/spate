/*
 * Rodzhang
 *
 */

#include "dpdk_netdev_ftbl.h"
#include "dpdk_netdev_pcap.h"
#include "../../dpdk_inc.h"
#include <spate_utils.h>

#ifdef USDT_ENABLE
#include <sys/sdt.h>
#endif

static uint16_t _dpdk_netdev_rx_vec(plane_dpdk_netdev_t *netdev, uint16_t queue_id,
        struct rte_mbuf **mbufs, uint16_t mbuf_size)
{
    uint16_t                rx_nr;

    rx_nr = rte_eth_rx_burst(netdev->port_id, queue_id, mbufs, mbuf_size);

    if (rx_nr == 0) {
        return 0;
    }

#ifdef USDT_ENABLE
    DTRACE_PROBE2(spate, dpdk_rx_vector, mbufs, mbuf_size);
#endif 

    __dpdk_netdev_pcap(mbufs, rx_nr, 1);

    return rx_nr;
}

static uint16_t _dpdk_netdev_tx_vec(plane_dpdk_netdev_t *netdev, uint16_t queue_id,
        struct rte_mbuf **mbufs, uint16_t mbuf_size)
{
    if (mbuf_size == 0) {
        return 0;
    }

#ifdef USDT_ENABLE
    DTRACE_PROBE2(spate, dpdk_tx_vector, mbufs, mbuf_size);
#endif 

    __dpdk_netdev_pcap(mbufs, mbuf_size, 0);

    return rte_eth_tx_burst(netdev->port_id, queue_id, mbufs, mbuf_size);
}


const plane_dpdk_netdev_ftbl_t c_dpdk_netdev_ftbl = {
    .rx_vec = _dpdk_netdev_rx_vec,
    .tx_vec = _dpdk_netdev_tx_vec,
};
