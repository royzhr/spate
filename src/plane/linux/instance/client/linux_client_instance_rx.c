/*
 * Rodzhang
 *
 */

#include "linux_client_instance_rx.h"
#include "../linux_instance_utils.h"



static inline uint16_t __linux_client_instance_process_pkts(client_instance_context_t *ctx,
        char **pkts, uint16_t *lens, uint16_t rx_nr, uint64_t now)
{
    client_instance_rx_param_t  rxp;
    int                         ret;
    uint16_t                    i;

    memset(&rxp, 0, sizeof(rxp));
    rxp.now = now;

    for (i=0; i<rx_nr; ++i) {

        rxp.pkt_data_len = lens[i];

        ret = ctx->fptr->on_recv_packet(ctx, pkts[i], lens[i], &rxp);

        if (likely(ret == INSTANCE_RX_RET_DROP)) {
            pkts[i] = NULL;
        } else {
            if (unlikely(rxp.pkt_data_len != lens[i])) {
                lens[i] = rxp.pkt_data_len;
            }
        }
    }

    return __strip_null_pkts(pkts, lens, rx_nr);
}


static inline void __linux_client_instance_rx_pkts(client_instance_context_t *ctx, 
        plane_linux_netdev_queue_t *queue, 
        char **rx_pkts, uint16_t *lens, uint16_t rx_nr, uint64_t now)
{
    char                        *pkts[rx_nr];
    uint16_t                    need_tx_nr, tx_nr;

    __copy_pkts(pkts, rx_pkts, rx_nr);

    need_tx_nr = __linux_client_instance_process_pkts(ctx, pkts, lens, rx_nr, now);

    tx_nr = __linux_queue_tx_pkts(queue, pkts, lens, need_tx_nr);
    
    ctx->fptr->on_stat_tx(ctx, tx_nr, need_tx_nr-tx_nr);
}

static inline uint16_t __linux_client_instance_rx(client_instance_context_t *ctx, 
        plane_linux_netdev_queue_t *queue, 
        char **rx_pkts, uint16_t *lens, uint16_t pkt_nr, uint64_t now)
{
    uint16_t                    rx_nr, rx_clean;
    
    rx_nr = queue->vptr->rx_get_pkts(queue, rx_pkts, lens, pkt_nr);

    __linux_client_instance_rx_pkts(ctx, queue, rx_pkts, lens, rx_nr, now);

    rx_clean = queue->vptr->rx_clean(queue, rx_pkts, rx_nr);
    ASSERT(rx_clean == rx_nr);

    return rx_clean;
}

void linux_client_instance_rx(client_instance_context_t *ctx, 
        plane_linux_netdev_queue_t *queue, uint64_t now)
{
    char                        *rx_pkts [SPATE_MAX_BURST];
    uint16_t                    lens     [SPATE_MAX_BURST];
    uint16_t                    nr;
    
    do {

        nr = __linux_client_instance_rx(ctx, queue, rx_pkts, lens, SPATE_MAX_BURST, now);

    } while (nr == SPATE_MAX_BURST);
}
