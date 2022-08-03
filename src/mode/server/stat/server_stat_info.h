/*
 * Rodzhang
 *
 */

#ifndef __SERVER_STAT_INFO_H__
#define __SERVER_STAT_INFO_H__


#include <spate_stat.h>
#include "../../../export/server/spate_server_stat.h"



void server_stat_info_zero(server_stat_info_t *cs);

void server_stat_info_copy(server_stat_info_t *dst, 
        const server_stat_info_t *src);


void server_stat_info_delta(server_stat_info_t *delta, 
        const server_stat_info_t *new, const server_stat_info_t *old);


#endif /* __SERVER_STAT_INFO_H__ */
