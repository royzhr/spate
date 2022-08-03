/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_packet.h>
#include <spate_session.h>
#include "dpdk_client_instance_tx.h"
#include "../../plane_dpdk_context.h"


static inline struct rte_mempool *__dpdk_client_instance_get_mbuf_pool(
        client_instance_context_t *ctx)
{
    plane_dpdk_context_t        *dpdk_ctx;

    dpdk_ctx = container_of(ctx->base.plane_ctx, plane_dpdk_context_t, base);

    return dpdk_ctx->percpu_block->mbuf_pool;
}

static inline void __mbuf_set_pkt_len(struct rte_mbuf *mbuf, uint16_t pkt_len)
{
    rte_pktmbuf_pkt_len(mbuf)  = pkt_len;
    rte_pktmbuf_data_len(mbuf) = pkt_len;
}
static inline void __mbufs_set_pkt_len(struct rte_mbuf **mbufs, 
        uint16_t *lens, uint16_t nr)
{
    uint16_t                i;

    for (i=0; i<nr; ++i) {
        __mbuf_set_pkt_len(mbufs[i], lens[i]);
    }
}

static inline void __extract_pkts_from_mbufs(char **pkts,
        struct rte_mbuf **mbufs, uint16_t mbuf_len)
{
    uint16_t                i;

    for (i=0; i<mbuf_len; ++i) {
        pkts[i] = (char*)mbufs[i]->buf_addr + mbufs[i]->data_off;
    }
}

static inline uint32_t __dpdk_client_instance_tx_generate_mbufs(client_instance_context_t *ctx, 
        uint64_t now, struct rte_mbuf **mbufs, uint16_t mbuf_len)
{
    char                    *pkts[mbuf_len];
    uint16_t                lens [mbuf_len];
    uint16_t                gen_nr;

    __extract_pkts_from_mbufs(pkts, mbufs, mbuf_len);

    gen_nr = g_session->ops->generate_pkts(ctx, now, pkts, lens, mbuf_len);

    __mbufs_set_pkt_len(mbufs, lens, gen_nr);

    return gen_nr;
}

static inline uint16_t __dpdk_client_instance_tx_alloc(client_instance_context_t *ctx,
        struct rte_mbuf **mbufs, uint16_t burst_nr)
{
    struct rte_mempool      *pool;
    uint16_t                i;

    pool = __dpdk_client_instance_get_mbuf_pool(ctx);

    for (i=0; i<burst_nr; ++i) {
        
        mbufs[i] = rte_pktmbuf_alloc(pool);

        if (unlikely(!mbufs[i])) {
            break;
        }
    }

    return i;
}

static inline void __dpdk_client_instance_tx_free_redundancy(client_instance_context_t *ctx,
        struct rte_mbuf **mbufs, uint16_t alloc_nr, uint16_t gen_nr)
{
    uint16_t                i;

    ASSERT(gen_nr <= alloc_nr);

    for (i=gen_nr; i<alloc_nr; ++i) {
        rte_pktmbuf_free(mbufs[i]);
        mbufs[i] = NULL;
    }
}


static inline void __dpdk_client_instance_tx_burst(client_instance_context_t *ctx, 
        uint64_t now, uint16_t burst_nr)
{
    struct rte_mbuf     *mbufs[burst_nr];
    uint16_t            queue_id;
    uint16_t            alloc_nr, gen_nr, tx_nr;
    plane_dpdk_netdev_t *dev;

    alloc_nr = __dpdk_client_instance_tx_alloc(ctx, mbufs, burst_nr);

    gen_nr = __dpdk_client_instance_tx_generate_mbufs(ctx, now, mbufs, alloc_nr);

    __dpdk_client_instance_tx_free_redundancy(ctx, mbufs, alloc_nr, gen_nr);

    queue_id = ctx->base.worker_id;
    dev      = __get_plane_dpdk_netdev();

    //hw send
    tx_nr = __dpdk_netdev_tx_mbufs(dev, queue_id, mbufs, gen_nr);

    ctx->fptr->on_stat_tx(ctx, tx_nr, gen_nr-tx_nr);
}

void dpdk_client_instance_tx(client_instance_context_t *ctx, uint64_t now)
{
    ASSERT(ctx->tc.tx_burst_nr <= SPATE_MAX_BURST);

    __dpdk_client_instance_tx_burst(ctx, now, ctx->tc.tx_burst_nr);
}



