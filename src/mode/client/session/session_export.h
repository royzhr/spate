/*
 * Rodzhang
 *
 */

#ifndef __SESSION_EXPORT_H__
#define __SESSION_EXPORT_H__


#include <stdint.h>
#include <spate_net_proto.h>
#include <spate_mode_client.h>

#include "session_cfg.h"

typedef enum {
    SESSION_GEN_NORMAL = 0,
    SESSION_GEN_TCP_SYNACK_ACK,
    SESSION_GEN_TCP_RST,

    SESSION_GEN_MAX
} session_generate_code_e;


typedef struct {

    /*
     * Param:
     * @ctx       : [Input] the context of client instance 
     * @now       : [Input] current cycles
     * @pkts      : [Input] vector of packets
     * @lens      : [Ouput] vector of length of packets
     * @pkt_nr    : [Input] count of packets
     *
     * Return Val: count of generate packtes
     *
     */
    uint16_t (*generate_pkts)(client_instance_context_t *ctx, uint64_t now, 
            char **pkts, uint16_t *lens, uint16_t pkt_nr);

    /*
     * Param:
     * @ctx       : [Input] the context of client instance 
     * @now       : [Input] current cycles
     * @sgc       : [Input] how to generate packet
     * @pkt       : [Input|Ouput] data of packet
     * @len       : [Ouput] length of packet
     *
     * Return Val: 
     * 0          : success
     * -1         : error
     */
    int (*generate_pkt)(client_instance_context_t *ctx, uint64_t now,
            session_generate_ctrl_t *sgc, char *pkt, uint16_t *len);
    

    uint32_t (*get_session_nr)(void);

    void (*on_tcp_update)(uint32_t sess_idx, tcp_hdr_t *tcp);

    void (*on_recv_tcp_rst)(ipv4_hdr_t *iphdr, tcp_hdr_t *tcp);

    /*
     * Assign session to worker
     * Param:
     * @sr        : [Ouput] the session which assign to worker
     * @worker_id : [Input] the worker_id
     * @worker_nr : [Input] Let Session Module not depend on the worker module
     *
     * Return Val : 
     * @ 0        : Success
     * @ -1       : Failed
     */
    int (*assign_to_worker)(session_roll_t *sr, uint16_t worker_id, uint16_t worker_nr);



} session_ops_t;

/*
 * the export of Session Module
 */
typedef struct {
    
    const session_ops_t     *ops;

    session_cfg_t           cfg;

} session_export_t;


extern session_export_t     *g_session;


#endif /* __SESSION_EXPORT_H__ */

