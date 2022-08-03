/*
 * Rodzhang
 *
 */

#include "session_generate_payload.h"
#include <spate_payload.h>


static inline void __generate_payload_struct(spate_payload_t *ps, 
        session_engress_t *engress, uint64_t now)
{
    uint32_t                sess_index;

    sess_index = engress - s_session_mgr->table.ses;

    __spate_payload_set_magic(ps);

    ps->flags = 0;

    memcpy(&ps->tx_cycles, &now, sizeof(now));
    memcpy(&ps->sess_index, &sess_index, sizeof(sess_index));
}

static inline void __generate_payload_padding(void *padding, uint16_t padding_len)
{
    memset(padding, 0, padding_len);
}

void generate_payload(void *payload, uint16_t payload_len, 
        session_engress_t *engress, uint64_t now)
{
    spate_payload_t         *ps;
    uint16_t                padding_len;

    ASSERT(payload_len == g_packet->cfg.payload_size);

    ps = (spate_payload_t *)payload;
    padding_len = payload_len - sizeof(*ps);
    
    __generate_payload_struct(ps, engress, now);

    if (padding_len) {
        __generate_payload_padding((void*)(ps+1), padding_len);
    }

}

