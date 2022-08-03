/*
 *  Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include "os_mgr.h"
#include "os_ops.h"

os_export_t *g_os     = NULL;
os_mgr_t    *s_os_mgr = NULL;


int  os_mgr_init()
{
    s_os_mgr = mm_vmalloc(sizeof(*s_os_mgr));
    if (!s_os_mgr) {
        return -1;
    }

    memset(s_os_mgr, 0, sizeof(*s_os_mgr));

    g_os = &s_os_mgr->_export;

    g_os->ops = & c_os_ops;

    s_os_mgr->sig_process = os_default_sig_func;

    return 0;
}

void os_mgr_exit()
{
    mm_vfree(s_os_mgr, sizeof(*s_os_mgr));

    s_os_mgr = NULL;
    g_os     = NULL;

}


