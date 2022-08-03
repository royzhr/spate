/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_main.h>
#include <spate_tick.h>
#include "dpdk_client_instance.h"
#include "dpdk_client_instance_loop.h"
#include "dpdk_client_instance_tx.h"
#include "dpdk_client_instance_rx.h"



static inline uint64_t __dpdk_client_instance_rx_until(client_instance_context_t *ctx, 
        uint64_t now, uint64_t until)
{

    do {
        
        dpdk_client_instance_rx(ctx, now);

        now = __plane_get_cycles();

    } while(now < until);

    return now - until;
}


void dpdk_client_instance_loop(client_instance_context_t *ctx)
{
    uint64_t                c1, c2;
    uint64_t                delta;

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
        dpdk_client_instance_tx(ctx, c1);

        /*
         * Rcv packet
         */
        __dpdk_client_instance_rx_until(ctx, c1, c2);

        if (g_main->force_quit) {
            break;
        }

    }


}

