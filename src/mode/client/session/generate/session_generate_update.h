/*
 * Rodzhang
 *
 */

#ifndef __SESSION_GENERATE_UPDATE_H__
#define __SESSION_GENERATE_UPDATE_H__

#include "../session_mgr.h"


session_engress_t *session_generate_update_tcp(session_engress_t *engress, 
        client_instance_context_t *ctx);

session_engress_t *session_generate_update_tcp_graceful(session_engress_t *engress, 
        client_instance_context_t *ctx);

static inline session_engress_t *__session_generate_update(session_engress_t *engress, 
        client_instance_context_t *ctx)
{
    if (engress->proto == SPATE_UDP) {
        return engress;
    } else {
        return session_generate_update_tcp(engress, ctx);
    }
}

#endif /* __SESSION_GENERATE_UPDATE_H__ */
