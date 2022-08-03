/*
 * Rodzhang
 *
 */

#ifndef __SESSION_GENERATE_H__
#define __SESSION_GENERATE_H__



#include <spate_core.h>
#include "../session_mgr.h"


/*
 * Param:
 * @ctx       : [Input] the context of client instance 
 * @now       : [Input] current cycles
 * @pkts      : [Input] vector of packets
 * @lens      : [Ouput] vector of length of packets
 * @pkt_nr    : [Input] count of packets
 * @worker_id : [Input] the worker who want to generate pkts
 *
 * Return Val: count of generate packtes
 *
 */
uint16_t session_generate_pkts(client_instance_context_t *ctx, uint64_t now, 
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
int session_generate_pkt(client_instance_context_t *ctx, uint64_t now,
        session_generate_ctrl_t *sgc, char *pkt, uint16_t *len);


#endif /* __SESSION_GENERATE_H__ */


