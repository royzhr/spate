/*
 *  Rodzhang
 *
 */

#include "http_accept_event_handler.h"
#include <spate_event.h>
#include "../http_mgr.h"
#include <signal.h>


static int _http_accept_on_event_quit(void *user_data, void *args)
{
    http_accept_imp_t           *imp;

    imp = (http_accept_imp_t *)user_data;

    pthread_cancel(imp->accept_thread);

    return 0;
}


int  http_accept_event_handler_create(http_accept_imp_t *imp)
{
    g_event->ops->register_handler(EVENT_QUIT, _http_accept_on_event_quit, imp);

    return 0;
}

void http_accept_event_handler_destroy(http_accept_imp_t *imp)
{
    g_event->ops->unregister_handler(EVENT_QUIT, _http_accept_on_event_quit, imp);
}


