/*
 * Rodzhang
 *
 */

#include "linux_server_instance_rx.h"
#include "../linux_instance_utils.h"


static inline uint16_t __linux_server_instance_process_pkts(server_instance_context_t *ctx,
        char **pkts, uint16_t *lens, uint16_t rx_nr)
{
    uint16_t                i;
    int                     ret;

    for (i=0; i<rx_nr; ++i) {
        ret = ctx->fptr->on_recv_packet(ctx, pkts[i], lens[i]);

        if (!ret) {
            pkts[i] = NULL;
        }
    }

    return __strip_null_pkts(pkts, lens, rx_nr);
}

static inline void __linux_server_instance_rx_pkts(server_instance_context_t *ctx, 
        plane_linux_netdev_queue_t *queue, 
        char **rx_pkts, uint16_t *lens, uint16_t rx_nr)
{

    char                    *pkts[rx_nr];
    uint16_t                need_tx_nr, tx_nr;

    __copy_pkts(pkts, rx_pkts, rx_nr);

    need_tx_nr = __linux_server_instance_process_pkts(ctx, pkts, lens, rx_nr);

    tx_nr = __linux_queue_tx_pkts(queue, pkts, lens, need_tx_nr);

    /*
     * stat
     */
    ctx->fptr->on_stat_inc(ctx, rx_nr, tx_nr, need_tx_nr-tx_nr);
}

static inline uint16_t __linux_server_instance_rx(server_instance_context_t *ctx, 
        plane_linux_netdev_queue_t *queue, 
        char **rx_pkts, uint16_t *lens, uint16_t pkt_nr)
{
    uint16_t                rx_nr, rx_clean;

    rx_nr = queue->vptr->rx_get_pkts(queue, rx_pkts, lens, pkt_nr);

    __linux_server_instance_rx_pkts(ctx, queue, rx_pkts, lens, rx_nr);

    rx_clean = queue->vptr->rx_clean(queue, rx_pkts, rx_nr);
    ASSERT(rx_clean == rx_nr);

    return rx_clean;
}

void linux_server_instance_rx(server_instance_context_t *ctx, 
        plane_linux_netdev_queue_t *queue)
{
    char                    *rx_pkts [SPATE_MAX_BURST];
    uint16_t                lens     [SPATE_MAX_BURST];
    uint16_t                nr;

    do {

        nr = __linux_server_instance_rx(ctx, queue, rx_pkts, lens, SPATE_MAX_BURST);

    } while (nr == SPATE_MAX_BURST);
}
