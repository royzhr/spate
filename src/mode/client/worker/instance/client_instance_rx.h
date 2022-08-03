/*
 * Rodzhang
 *
 */

#ifndef __CLIENT_INSTANCE_RX_H__
#define __CLIENT_INSTANCE_RX_H__


#include <spate_core.h>
#include "client_instance_context.h"

int client_instance_on_recv_packet(client_instance_context_t *ctx, char *pkt_data, 
        uint16_t pkt_len, client_instance_rx_param_t *rxp);



#endif /* __CLIENT_INSTANCE_RX_H__ */
