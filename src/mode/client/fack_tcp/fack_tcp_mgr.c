/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include "fack_tcp_mgr.h"


fack_tcp_mgr_t       *s_fack_tcp_mgr    = NULL;
fack_tcp_export_t    *g_fack_tcp        = NULL;


int  fack_tcp_mgr_init(void)
{
    s_fack_tcp_mgr = mm_vmalloc(sizeof(*s_fack_tcp_mgr));

    if (!s_fack_tcp_mgr) {
        return -1;
    }

    memset(s_fack_tcp_mgr, 0, sizeof(*s_fack_tcp_mgr));

    g_fack_tcp = &s_fack_tcp_mgr->_export;

    return 0;
}

int  fack_tcp_mgr_setting(void)
{

    return 0;
}

void fack_tcp_mgr_exit(void)
{
    ASSERT(s_fack_tcp_mgr);

    mm_vfree(s_fack_tcp_mgr, sizeof(*s_fack_tcp_mgr));

    s_fack_tcp_mgr = NULL;
    g_fack_tcp     = NULL;
}


