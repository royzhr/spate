/*
 * Rodzhang
 *
 */

#ifndef __SESSION_STRUCT_H__
#define __SESSION_STRUCT_H__

#include <spate_core.h>


typedef enum {
    ST_IDLE = 0,
    ST_SYN_SEND,
    ST_ESTABLISH,
    ST_FIN_SEND,
    ST_CLOSE,
} spate_tcp_state_e;


typedef struct {

    /*
     * The following fields are defined as host byte order:
     *
     */
    uint32_t        sip;
    uint32_t        dip;
    uint16_t        sport;
    uint16_t        dport;

    uint32_t        proto   : 4,
                    state   : 5,    /* spate_tcp_state_e for TCP */
                    retrans : 1,
                    tick_id : 22;

    uint32_t        sequence;

} __attribute__((__packed__)) session_engress_t;


typedef struct {

    union {
        struct {
            uint8_t     syn_recv;
            uint8_t     fin_recv;
            uint8_t     rst_recv;
            uint8_t     tcp_reserve[1];
        } tcp;

        struct {
            uint32_t    udp_reserve;
        } udp;

        uint32_t        uint_val;
    };

} session_ingress_t;



#endif /* __SESSION_STRUCT_H__ */
