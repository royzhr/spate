/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_main.h>
#include <spate_plane.h>
#include "linux_client_instance.h"
#include "linux_client_instance_loop.h"
#include "linux_client_instance_tx.h"
#include "linux_client_instance_rx.h"


static inline void __linux_client_rx_may_wait(plane_linux_netdev_queue_t *queue, 
        uint64_t now, uint64_t until)
{
    uint32_t                usec;

    usec = __spate_cycles_to_usec(until - now);

    if (usec > 0) {
        queue->vptr->rx_wait(queue, usec);
    }
}


static inline uint64_t __linux_client_instance_rx_until(client_instance_context_t *ctx, 
        plane_linux_netdev_queue_t *queue, uint64_t now, uint64_t until)
{
    do {

        linux_client_instance_rx(ctx, queue, now);

        __linux_client_rx_may_wait(queue, now, until);

        now = __plane_get_cycles();

    } while(now < until);

    return now - until;
}


void linux_client_instance_loop(client_instance_context_t *ctx)
{
    uint64_t                    c1, c2;
    uint64_t                    delta;
    plane_linux_netdev_queue_t  *queue;

    queue = __get_plane_linux_netdev_queue(ctx->base.worker_id);

    delta = 0;

    for ( ; ; ) {
    
        c1 = __plane_get_cycles();

        if (delta < ctx->tc.tx_burst_cycles) {
            c2 = c1 + ctx->tc.tx_burst_cycles - delta;
        } else {
            c2 = c1 + ctx->tc.tx_burst_cycles;
        }
        
        /*
         * Build and send packet
         */
        linux_client_instance_tx(ctx, queue, c1);

        /*
         * Rcv packet
         */
        delta = __linux_client_instance_rx_until(ctx, queue, c1, c2);

        if (g_main->force_quit) {
            break;
        }

    }


}

