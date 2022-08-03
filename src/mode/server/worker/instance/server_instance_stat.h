/*
 * Rodzhang
 *
 */

#ifndef __SERVER_INSTANCE_STAT_H__
#define __SERVER_INSTANCE_STAT_H__


#include "server_instance_context.h"


void server_instance_on_stat_inc(server_instance_context_t *ctx,
        uint16_t rx_nr, uint16_t tx_nr, uint16_t busy_nr);

void server_instance_on_stat_update(server_instance_context_t *ctx,
        uint64_t rx_nr, uint64_t tx_nr, uint64_t busy_nr);


#endif /* __SERVER_INSTANCE_STAT_H__ */
