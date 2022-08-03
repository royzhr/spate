/*
 *  Rodzhang
 *
 */

#include "client_http_module.h"
#include "client_http_bridge.h"


static int _client_http_module_init(void)
{

    g_http->ops->register_httpget_handler(client_http_bridge_get, NULL);

    return 0;
}

static int _client_http_module_setting(void)
{

    return 0;
}

static void _client_http_module_exit(void)
{
    g_http->ops->unregister_httpget_handler(client_http_bridge_get, NULL);
}

const module_class_t c_client_http_module = {
    .module_name    = "client_http",
    .cfg_ops        = NULL,
    .module_init    = _client_http_module_init,
    .module_setting = _client_http_module_setting,
    .module_exit    = _client_http_module_exit,
};


