/*
 *  Rodzhang
 *
 */

#include "http_ops.h"
#include "http_mgr.h"


static int _http_register_get_handler(httpget_handler_fn fn, void *ud)
{
    http_handler_t          *handler;

    handler = s_http_mgr->http_handler;

    return handler->vptr->register_get_handler(handler, fn, ud);;
}

static void _http_unregister_get_handler(httpget_handler_fn fn, void *ud)
{
    http_handler_t          *handler;

    handler = s_http_mgr->http_handler;

    handler->vptr->unregister_get_handler(handler, fn, ud);;
}

const http_ops_t c_http_ops = {
    .register_httpget_handler   = _http_register_get_handler,
    .unregister_httpget_handler = _http_unregister_get_handler,
};


