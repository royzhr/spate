/*
 *  Rodzhang
 *
 */

#ifndef __HTTP_ACCEPT_SOCKET_H__
#define __HTTP_ACCEPT_SOCKET_H__


#include "http_accept_imp.h"

int  http_accept_socket_create(http_accept_imp_t *imp);
void http_accept_socket_destroy(http_accept_imp_t *imp);


#endif /* __HTTP_ACCEPT_SOCKET_H__ */
