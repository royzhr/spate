/*
 *  Rodzhang
 *
 */

#ifndef __HTTP_ACCEPT_H__
#define __HTTP_ACCEPT_H__


#include <spate_core.h>
#include "../http_cfg.h"

struct _http_accept_s;

typedef struct {
    
    void (*destroy)(struct _http_accept_s *my);

} http_accept_vtbl_t;

typedef struct _http_accept_s {

    const http_accept_vtbl_t    *vptr;

} http_accept_t;


http_accept_t *http_accept_create(const http_cfg_t *cfg);


#endif /* __HTTP_ACCEPT_H__ */
