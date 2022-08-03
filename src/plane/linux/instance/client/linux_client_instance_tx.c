/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_packet.h>
#include <spate_session.h>
#include "linux_client_instance_tx.h"
#include "../../plane_linux_context.h"


static inline void __linux_client_instance_tx_burst(client_instance_context_t *ctx,
        plane_linux_netdev_queue_t *queue, uint64_t now, uint16_t burst_nr)
{
    char                *pkts[burst_nr];
    uint16_t            lens [burst_nr];
    uint16_t            idle_nr, gen_nr, tx_nr;
    
    idle_nr = queue->vptr->tx_get_idle(queue, pkts, NULL, burst_nr);

    gen_nr = g_session->ops->generate_pkts(ctx, now, pkts, lens, idle_nr);

    tx_nr = queue->vptr->tx_xmit(queue, pkts, lens, gen_nr);
    ASSERT(tx_nr == gen_nr);

    if (tx_nr) {
        queue->vptr->tx_flush(queue, lens, tx_nr);
    }

    ctx->fptr->on_stat_tx(ctx, tx_nr, burst_nr-idle_nr);
}


void linux_client_instance_tx(client_instance_context_t *ctx, 
        plane_linux_netdev_queue_t *queue,uint64_t now)
{
    ASSERT(ctx->tc.tx_burst_nr <= SPATE_MAX_BURST);

    __linux_client_instance_tx_burst(ctx, queue, now, ctx->tc.tx_burst_nr);
}



