/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include "server_listen_mgr.h"


server_listen_export_t     *g_server_listen     = NULL;
server_listen_mgr_t        *s_server_listen_mgr = NULL;

int  server_listen_mgr_init(void)
{
    s_server_listen_mgr = mm_vmalloc(sizeof(*s_server_listen_mgr));
    
    if (!s_server_listen_mgr) {
        return -1;
    }

    memset(s_server_listen_mgr, 0, sizeof(*s_server_listen_mgr));

    g_server_listen = &s_server_listen_mgr->_export;

    return 0;
}

int  server_listen_mgr_setting(void)
{
    return 0;
}

void server_listen_mgr_exit(void)
{
    mm_vfree(s_server_listen_mgr, sizeof(*s_server_listen_mgr));

    s_server_listen_mgr = NULL;
    g_server_listen     = NULL;
}

