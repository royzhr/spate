/*
 *  Rodzhang
 *
 */

#ifndef __HTTP_ACCEPT_EVENT_HANDLER_H__
#define __HTTP_ACCEPT_EVENT_HANDLER_H__


#include "http_accept_imp.h"

int  http_accept_event_handler_create(http_accept_imp_t *imp);
void http_accept_event_handler_destroy(http_accept_imp_t *imp);



#endif /* __HTTP_ACCEPT_EVENT_HANDLER_H__ */
