/*
 *  Rodzhang
 *
 */

#include <spate_core.h>
#include "http_accept_method.h"
#include "http_accept_vtbl.h"
#include "http_accept_thread.h"
#include "http_accept_socket.h"
#include "http_accept_event_handler.h"


int  http_accept_constructor(http_accept_imp_t *imp)
{
    memset(imp, 0, sizeof(*imp));

    imp->base.vptr = &c_http_accept_vtbl;

    if (http_accept_socket_create(imp) < 0) {
        return -1;
    }

    if (http_accept_thread_create(imp) < 0) {
        http_accept_socket_destroy(imp);
        return -1;
    }

    if (http_accept_event_handler_create(imp) < 0) {
        http_accept_thread_destroy(imp);
        http_accept_socket_destroy(imp);
        return -1;
    }

    return 0;
}

void http_accept_destructor(http_accept_imp_t *imp)
{
    http_accept_event_handler_destroy(imp);

    http_accept_thread_destroy(imp);

    http_accept_socket_destroy(imp);
    
    imp->base.vptr = NULL;

}


