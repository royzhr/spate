/*
 * Rodzhang
 *
 */

#include "dpdk_client_instance_rx.h"
#include "../dpdk_instance_utils.h"

#ifdef USDT_ENABLE
#include <sys/sdt.h>
#endif

static inline int __dpdk_client_instance_process_mbuf(client_instance_context_t *ctx,
        struct rte_mbuf *mbuf, client_instance_rx_param_t *rxp)
{
    char                    *pkt_data;
    uint16_t                pkt_len;

    DPDK_PACKET_MBUF(pkt_data, pkt_len, mbuf);

#ifdef USDT_ENABLE
    DTRACE_PROBE2(spate, dpdk_rx, pkt_data, (uint64_t)pkt_len);
#endif

    return ctx->fptr->on_recv_packet(ctx, pkt_data, pkt_len, rxp);
}

static inline uint16_t __dpdk_client_instance_rx_mbufs(client_instance_context_t *ctx, 
        struct rte_mbuf **mbufs, uint16_t rx_nr, uint64_t now)
{
    uint16_t                    i;
    int                         ret;
    client_instance_rx_param_t  rxp;

    memset(&rxp, 0, sizeof(rxp));
    rxp.now = now;

    for (i=0; i<rx_nr; ++i) {

        rxp.pkt_data_len = mbufs[i]->data_len;

        ret = __dpdk_client_instance_process_mbuf(ctx, mbufs[i], &rxp);

        if (likely(ret == INSTANCE_RX_RET_DROP)) {
            rte_pktmbuf_free(mbufs[i]);
            mbufs[i] = NULL;
        } else {
            if (unlikely(rxp.pkt_data_len != mbufs[i]->data_len)) {
                rte_pktmbuf_pkt_len(mbufs[i])  = rxp.pkt_data_len;
                rte_pktmbuf_data_len(mbufs[i]) = rxp.pkt_data_len;
            }
        }
    }

    return __strip_null_mbuf(mbufs, rx_nr);
}

void dpdk_client_instance_rx(client_instance_context_t *ctx, uint64_t now)
{
    struct rte_mbuf     *mbufs[SPATE_MAX_BURST];
    uint16_t            rx_nr, need_tx_nr, tx_nr;
    uint16_t            queue_id;
    plane_dpdk_netdev_t *dev;

    queue_id = ctx->base.worker_id;

    dev = __get_plane_dpdk_netdev();

    rx_nr = __dpdk_netdev_rx_mbufs(dev, queue_id, mbufs, SPATE_MAX_BURST);

    need_tx_nr = __dpdk_client_instance_rx_mbufs(ctx, mbufs, rx_nr, now);

    tx_nr = __dpdk_netdev_tx_mbufs(dev, queue_id, mbufs, need_tx_nr);

    ctx->fptr->on_stat_tx(ctx, tx_nr, need_tx_nr-tx_nr);
}
