/*
 * Rodzhang
 *
 */

#include "dpdk_server_instance_rx.h"
#include "../dpdk_instance_utils.h"

/*
 * Return Value:
 * 0    : Drop
 * 1    : need to tx
 */
static inline int __dpdk_server_instance_process_mbuf(server_instance_context_t *ctx, 
        struct rte_mbuf *mbuf)
{
    char                    *pkt_data;
    uint16_t                pkt_len;

    DPDK_PACKET_MBUF(pkt_data, pkt_len, mbuf);

    return ctx->fptr->on_recv_packet(ctx, pkt_data, pkt_len);
}




static inline uint16_t __dpdk_server_instance_rx_mbufs(server_instance_context_t *ctx,
        struct rte_mbuf **mbufs, uint16_t rx_nr)
{
    uint16_t                i;
    int                     ret;

    for (i=0; i<rx_nr; ++i) {
        ret = __dpdk_server_instance_process_mbuf(ctx, mbufs[i]);

        if (!ret) {
            rte_pktmbuf_free(mbufs[i]);
            mbufs[i] = NULL;
        }
    }

    return __strip_null_mbuf(mbufs, rx_nr);
}

void dpdk_server_instance_rx(server_instance_context_t *ctx)
{
    struct rte_mbuf     *mbufs[SPATE_MAX_BURST];
    uint16_t            rx_nr, need_tx_nr, tx_nr;
    uint16_t            queue_id;
    plane_dpdk_netdev_t *dev;

    queue_id = ctx->base.worker_id;

    dev = __get_plane_dpdk_netdev();

    rx_nr = __dpdk_netdev_rx_mbufs(dev, queue_id, mbufs, SPATE_MAX_BURST);

    need_tx_nr = __dpdk_server_instance_rx_mbufs(ctx, mbufs, rx_nr);

    tx_nr = __dpdk_netdev_tx_mbufs(dev, queue_id, mbufs, need_tx_nr);

    /*
     * stat
     */
    ctx->fptr->on_stat_inc(ctx, rx_nr, tx_nr, need_tx_nr-tx_nr);
}
