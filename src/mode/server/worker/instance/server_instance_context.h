/*
 * Rodzhang
 *
 */

#ifndef __SERVER_INSTANCE_CONTEXT_H__
#define __SERVER_INSTANCE_CONTEXT_H__


#include <spate_core.h>
#include <spate_instance.h>
#include "../../stat/server_stat_info.h"

struct _server_instance_context_s;

typedef struct {

    /*
     * Return Value:
     * 0    : drop
     * 1    : need to tx
     */
    int (*on_recv_packet)(struct _server_instance_context_s *my,
            char *pkt_data, uint16_t pkt_len);

    void (*on_stat_inc)(struct _server_instance_context_s *my,
            uint16_t rx_nr, uint16_t tx_nr, uint16_t busy_nr);

    void (*on_stat_update)(struct _server_instance_context_s *my,
            uint64_t rx_nr, uint64_t tx_nr, uint64_t busy_nr);

} server_instance_ftbl_t;


typedef struct _server_instance_context_s {


    instance_context_t              base;


    /*
     * Function table
     */
    const server_instance_ftbl_t    *fptr;

    /*
     * Stat
     */
    server_stat_info_t              stat_info;



}__attribute__((__aligned__(128))) server_instance_context_t;




static inline server_stat_info_t *__ctx_get_server_stat_info(server_instance_context_t *ctx)
{
    return &ctx->stat_info;
}



#endif /* __SERVER_INSTANCE_CONTEXT_H__ */
