/*
 * Rodzhang
 *
 */

#include "client_worker_ops.h"
#include "client_worker_mgr.h"


static uint16_t _client_worker_get_worker_nr(void)
{
    return s_client_worker_mgr->worker_nr;
}

static const client_stat_info_t *_client_worker_get_client_stat_info(uint16_t worker_id)
{
    client_instance_context_t   *ctx;

    ASSERT(worker_id < s_client_worker_mgr->worker_nr);

    ctx = &s_client_worker_mgr->contexts[worker_id];
    
    return &ctx->stat_info;
}

static const client_stat_info_t *_client_worker_get_extend_stat_info()
{
    client_extend_stat_handler_t   *handler;

    handler = &s_client_worker_mgr->extend_stat_handler;

    if (handler->func) {
        return handler->func(handler->user_data);
    }

    return NULL;
}

static int _client_worker_register_extend_stat_handler(extend_client_stat_fn fn, void *ud)
{
    client_extend_stat_handler_t   *handler;

    handler = &s_client_worker_mgr->extend_stat_handler;

    if (handler->func) {
        return -1;
    }

    handler->func      = fn;
    handler->user_data = ud;

    return 0;
}

static void _client_worker_unregister_extend_stat_handler(extend_client_stat_fn fn, void *ud)
{
    client_extend_stat_handler_t   *handler;

    handler = &s_client_worker_mgr->extend_stat_handler;

    ASSERT(handler->func == fn);

    handler->func      = NULL;
    handler->user_data = NULL;
}

const client_worker_ops_t c_client_worker_ops = {
    .get_worker_nr                         = _client_worker_get_worker_nr,
    .get_client_stat_info                  = _client_worker_get_client_stat_info,
    .get_client_extend_stat_info           = _client_worker_get_extend_stat_info,
    .register_client_extend_stat_handler   = _client_worker_register_extend_stat_handler,
    .unregister_client_extend_stat_handler = _client_worker_unregister_extend_stat_handler,
};
