/*
 * Rodzhang
 *
 */

#ifndef __SESSION_GENERATE_VXLAN_H__
#define __SESSION_GENERATE_VXLAN_H__


#include <spate_core.h>
#include "../session_mgr.h"


uint16_t generate_vxlan_packet_data(client_instance_context_t *ctx, 
        session_engress_t * engress, char *pkt_data, uint64_t now, uint32_t gen_code);


#endif /* __SESSION_GENERATE_VXLAN_H__ */

