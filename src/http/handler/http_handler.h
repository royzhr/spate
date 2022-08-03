/*
 *  Rodzhang
 *
 */

#ifndef __HTTP_HANDLER_H__
#define __HTTP_HANDLER_H__


#include <spate_core.h>
#include "../http_export.h"


struct _http_handler_s;

typedef struct {

    int  (*register_get_handler)(struct _http_handler_s *my, httpget_handler_fn fn, void *ud);
    void (*unregister_get_handler)(struct _http_handler_s *my, httpget_handler_fn fn, void *ud);

    int  (*call_get_handler)(struct _http_handler_s *my, const char *uri, 
            char *buf, int size, int *len);

    void (*destroy)(struct _http_handler_s *my);

} http_handler_vtbl_t;

typedef struct _http_handler_s {

    const http_handler_vtbl_t   *vptr;

} http_handler_t;


http_handler_t *http_handler_create(void);


#endif /* __HTTP_HANDLER_H__ */

