/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_main.h>
#include "linux_server_instance_loop.h"
#include "linux_server_instance_rx.h"


void linux_server_instance_loop(server_instance_context_t *ctx)
{
    plane_linux_netdev_queue_t  *queue;

    queue = __get_plane_linux_netdev_queue(ctx->base.worker_id);

    ASSERT(queue->vptr->get_id(queue) == ctx->base.worker_id);

    for ( ; ; ) {

        /*
         * timeout: 100ms
         */
        queue->vptr->rx_wait(queue, 100000);

        /*
         * Rcv packet
         */
        linux_server_instance_rx(ctx, queue);

        if (g_main->force_quit) {
            break;
        }
    }

}


