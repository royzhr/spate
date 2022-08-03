/*
 * Rodzhang
 *
 */

#include "server_worker_ops.h"
#include "server_worker_mgr.h"


static uint16_t _server_worker_get_worker_nr(void)
{
    return s_server_worker_mgr->worker_nr;
}

static const server_stat_info_t *_server_worker_get_server_stat_info(uint16_t worker_id)
{
    server_instance_context_t   *ctx;

    ASSERT(worker_id < s_server_worker_mgr->worker_nr);

    ctx = &s_server_worker_mgr->contexts[worker_id];
    
    return &ctx->stat_info;
}

static const server_stat_info_t *_server_worker_get_extend_stat_info()
{
    server_extend_stat_handler_t   *handler;

    handler = &s_server_worker_mgr->extend_stat_handler;

    if (handler->func) {
        return handler->func(handler->user_data);
    }

    return NULL;
}

static int _server_worker_register_extend_stat_handler(extend_server_stat_fn fn, void *ud)
{
    server_extend_stat_handler_t   *handler;

    handler = &s_server_worker_mgr->extend_stat_handler;

    if (handler->func) {
        return -1;
    }

    handler->func      = fn;
    handler->user_data = ud;

    return 0;
}

static void _server_worker_unregister_extend_stat_handler(extend_server_stat_fn fn, void *ud)
{
    server_extend_stat_handler_t   *handler;

    handler = &s_server_worker_mgr->extend_stat_handler;

    ASSERT(handler->func == fn);

    handler->func      = NULL;
    handler->user_data = NULL;
}

const server_worker_ops_t c_server_worker_ops = {
    .get_worker_nr                         = _server_worker_get_worker_nr,
    .get_server_stat_info                  = _server_worker_get_server_stat_info,
    .get_server_extend_stat_info           = _server_worker_get_extend_stat_info,
    .register_server_extend_stat_handler   = _server_worker_register_extend_stat_handler,
    .unregister_server_extend_stat_handler = _server_worker_unregister_extend_stat_handler,
};


