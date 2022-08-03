/*
 * Rodzhang
 *
 */

#ifndef __SESSION_GENERATE_PAYLOAD_H__
#define __SESSION_GENERATE_PAYLOAD_H__


#include <spate_core.h>
#include <spate_packet.h>
#include "../session_mgr.h"

static inline uint16_t __generate_payload_get_len(void)
{
    ASSERT(g_packet->cfg.payload_size >= SPATE_MIN_PAYLOAD);

    return g_packet->cfg.payload_size;
}

void generate_payload(void *payload, uint16_t payload_len, 
        session_engress_t *engress, uint64_t now);



#endif /* __SESSION_GENERATE_PAYLOAD_H__ */

