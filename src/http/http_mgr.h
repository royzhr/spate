/*
 *  Rodzhang
 *
 */

#ifndef __HTTP_MGR_H__
#define __HTTP_MGR_H__


#include <spate_core.h>
#include "http_cfg.h"
#include "http_export.h"
#include "accept/http_accept.h"
#include "handler/http_handler.h"


typedef struct {

    http_export_t       _export;

    http_cfg_t          cfg;

    http_accept_t       *http_accept;

    http_handler_t      *http_handler;

} http_mgr_t;


int  http_mgr_init(void);
int  http_mgr_setting(void);
void http_mgr_exit(void);


extern http_mgr_t   *s_http_mgr;

static inline http_cfg_t *__http_cfg_block_get(void)
{
    return &s_http_mgr->cfg;
}



#endif /* __HTTP_MGR_H__ */
