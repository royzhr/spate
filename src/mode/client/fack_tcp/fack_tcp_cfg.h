/*
 * Rodzhang
 *
 */

#ifndef __FACK_TCP_CFG_H__
#define __FACK_TCP_CFG_H__


#include <spate_core.h>
#include <spate_config.h>
#include <spate_module.h>

typedef struct {
    
    uint16_t        syn_retrans_time;
    uint16_t        fin_retrans_time;

    uint16_t        close_wait_time;

    uint16_t        establish_time;

    int             synack_ack_enable;

    uint16_t        quit_graceful_timeout;

} fack_tcp_cfg_t;



#endif /* __FACK_TCP_CFG_H__ */
