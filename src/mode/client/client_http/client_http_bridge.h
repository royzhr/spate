/*
 *  Rodzhang
 *
 */

#ifndef __CLIENT_HTTP_BRIDGE_H__
#define __CLIENT_HTTP_BRIDGE_H__


#include <spate_core.h>
#include <spate_http.h>

int client_http_bridge_get(void *ud, const char *uri, char *buf, int size, int *len);


#endif /* __CLIENT_HTTP_BRIDGE_H__ */
