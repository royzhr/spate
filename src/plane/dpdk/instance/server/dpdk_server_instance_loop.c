/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_main.h>
#include "dpdk_server_instance_loop.h"
#include "dpdk_server_instance_rx.h"



void dpdk_server_instance_loop(server_instance_context_t *ctx)
{
    for ( ; ; ) {

        /*
         * Rcv packet
         */
        dpdk_server_instance_rx(ctx);

        if (g_main->force_quit) {
            break;
        }
    }

}


