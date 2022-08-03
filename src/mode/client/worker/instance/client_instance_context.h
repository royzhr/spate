/*
 * Rodzhang
 *
 */

#ifndef __CLIENT_INSTANCE_CONTEXT_H__
#define __CLIENT_INSTANCE_CONTEXT_H__


#include <spate_core.h>
#include <spate_instance.h>
#include "../../stat/client_stat_info.h"

struct _client_instance_context_s;

typedef struct {
    
    uint32_t                    sess_index;
    uint32_t                    generate_code;

} session_generate_ctrl_t;

#define CLIENT_RX_STAT_BUG_CODE_VXLAN    1
typedef struct {
    uint32_t                    us_latency;
    uint32_t                    bug_code;
} client_instance_rx_stat_param_t;

typedef struct {

    /*
     * input
     */
    uint64_t                        now;

    /*
     * output on return value of CLIENT_RX_RET_STAT
     */
    uint8_t                         need_stat;
    uint8_t                         need_session_generate;

    /*
     * The size of packet may change if it need to tx.
     */
    uint16_t                        pkt_data_len;

    session_generate_ctrl_t         session_generate_ctrl;
    client_instance_rx_stat_param_t rx_stat_param;

} client_instance_rx_param_t;

typedef struct {

    /*
     * rx on client instance
     */
    int (*on_recv_packet)(struct _client_instance_context_s *my, char *pkt_data,
            uint16_t pkt_len, client_instance_rx_param_t *rxp);

    void (*on_stat_tx)(struct _client_instance_context_s *my, uint16_t tx_nr, uint16_t busy_nr);

} client_instance_ftbl_t;



typedef struct {
    
    /* 
     * Calculate brust_nr(pkts per burst) according to the sending rate:
     */
    uint32_t                tx_burst_nr;
    
    uint16_t                packet_id;

    /*
     * Cycles to spend for each batch of brust to be sent
     */
    uint64_t                tx_burst_cycles;

} traffic_controller_t;


typedef struct {

    /* 
     * [ )
     */
    uint32_t        sess_idx_begin, sess_idx_end;
    
    uint32_t        sess_idx_curr;

} session_roll_t;




/*
 * client worker (percpu) 's context
 */
typedef struct _client_instance_context_s {
    
    instance_context_t              base;

    /*
     * Function table
     */
    const client_instance_ftbl_t    *fptr;


    traffic_controller_t            tc;

    session_roll_t                  session_roll;

    
    /*
     * stat 
     */
    client_stat_info_t              stat_info;


}__attribute__((__aligned__(128))) client_instance_context_t;




static inline client_stat_info_t *__ctx_get_client_stat_info(client_instance_context_t *ctx)
{
    return &ctx->stat_info;
}





#endif /* __CLIENT_INSTANCE_CONTEXT_H__ */


