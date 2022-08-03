/*
 * Rodzhang
 *
 */

#ifndef __CLIENT_INSTANCE_STAT_H__
#define __CLIENT_INSTANCE_STAT_H__


#include "client_instance_context.h"

void client_instance_stat_rx(client_instance_context_t *ctx, client_instance_rx_stat_param_t *sp);

void client_instance_stat_tx(client_instance_context_t *ctx, uint16_t tx_nr, uint16_t busy_nr);


#endif /* __CLIENT_INSTANCE_STAT_H__ */
