/*
 * Rodzhang
 *
 */

#ifndef __LINUX_CLIENT_INSTANCE_RX_H__
#define __LINUX_CLIENT_INSTANCE_RX_H__


#include "linux_client_instance.h"

void linux_client_instance_rx(client_instance_context_t *ctx, 
        plane_linux_netdev_queue_t *queue, uint64_t now);


#endif /* __LINUX_CLIENT_INSTANCE_RX_H__ */
