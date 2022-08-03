/*
 *  Rodzhang
 *
 */


#include <spate_core.h>
#include <spate_mm.h>
#include <spate_main.h>
#include "http_mgr.h"
#include "http_ops.h"


http_export_t    *g_http        = NULL;
http_mgr_t       *s_http_mgr    = NULL;


int  http_mgr_init(void)
{
    s_http_mgr = mm_vmalloc(sizeof(*s_http_mgr));

    if (!s_http_mgr) {
        return -1;
    }

    memset(s_http_mgr, 0, sizeof(*s_http_mgr));

    g_http = &s_http_mgr->_export;

    g_http->ops = &c_http_ops;

    s_http_mgr->http_handler = http_handler_create();
    if (!s_http_mgr->http_handler) {
        return -1;
    }

    return 0;
}

int  http_mgr_setting(void)
{
    if (s_http_mgr->cfg.enable) {
        s_http_mgr->http_accept = http_accept_create(__http_cfg_block_get());
        if (!s_http_mgr->http_accept) {
            return -1;
        }
    }

    return 0;
}

void http_mgr_exit(void)
{
    ASSERT(s_http_mgr);

    if (s_http_mgr->cfg.enable) {
        s_http_mgr->http_accept->vptr->destroy(s_http_mgr->http_accept);
        s_http_mgr->http_accept = NULL;
    }

    s_http_mgr->http_handler->vptr->destroy(s_http_mgr->http_handler);

    mm_vfree(s_http_mgr, sizeof(*s_http_mgr));

    g_http     = NULL;
    s_http_mgr = NULL;
}




