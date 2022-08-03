/*
 *  Rodzhang
 *
 */

#include "http_handler_vtbl.h"
#include "http_handler_method.h"
#include <spate_mm.h>
#include <spate_utils.h>


static int _http_handler_register_get(http_handler_t *my, 
        httpget_handler_fn fn, void *ud)
{
    http_handler_imp_t          *imp;

    imp = container_of(my, http_handler_imp_t, base);

    if (imp->get_handler) {
        return -1;
    }

    imp->get_handler    = fn;
    imp->get_handler_ud = ud;

    return 0;
}

static void _http_handler_unregister_get(http_handler_t *my, 
        httpget_handler_fn fn, void *ud)
{
    http_handler_imp_t          *imp;

    imp = container_of(my, http_handler_imp_t, base);

    ASSERT(fn == imp->get_handler);

    imp->get_handler    = NULL;
    imp->get_handler_ud = NULL;
}

static int _http_handler_call_get(http_handler_t *my, const char *uri, 
        char *buf, int size, int *len)
{
    http_handler_imp_t          *imp;
    int                         ret;

    imp = container_of(my, http_handler_imp_t, base);

    ret = 0;

    if (imp->get_handler) {
        ret = imp->get_handler(imp->get_handler_ud, uri, buf, size, len);
    }

    return ret;
}

static void _http_handler_destroy(http_handler_t *my)
{
    http_handler_imp_t          *imp;

    imp = container_of(my, http_handler_imp_t, base);

    http_handler_destructor(imp);

    mm_vfree(imp, sizeof(*imp));
}

const http_handler_vtbl_t c_http_handler_vtbl = {
    .register_get_handler   = _http_handler_register_get,
    .unregister_get_handler = _http_handler_unregister_get,
    .call_get_handler       = _http_handler_call_get,
    .destroy                = _http_handler_destroy,
};


