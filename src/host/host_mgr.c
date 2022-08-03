/*
 * Rodzhang
 *
 */


#include <spate_mm.h>
#include "host_mgr.h"
#include "host_ops.h"


host_export_t    *g_host      = NULL;
host_mgr_t       *s_host_mgr  = NULL;


int  host_mgr_init(void)
{
    s_host_mgr = mm_vmalloc(sizeof(*s_host_mgr));

    if (!s_host_mgr) {
        return -1;
    }

    memset(s_host_mgr, 0, sizeof(*s_host_mgr));

    g_host = &s_host_mgr->_export;
    g_host->ops = &c_host_ops;

    return 0;
}

int  host_mgr_setting(void)
{
    return 0;
}

void host_mgr_exit(void)
{
    mm_vfree(s_host_mgr, sizeof(*s_host_mgr));

    s_host_mgr = NULL;
    g_host     = NULL;
}

