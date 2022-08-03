/*
 * Rodzhang
 *
 */


#include <spate_mm.h>
#include "hook_mgr.h"


hook_export_t    *g_hook      = NULL;
hook_mgr_t       *s_hook_mgr  = NULL;


int  hook_mgr_init(void)
{
    s_hook_mgr = mm_vmalloc(sizeof(*s_hook_mgr));

    if (!s_hook_mgr) {
        return -1;
    }

    memset(s_hook_mgr, 0, sizeof(*s_hook_mgr));

    g_hook = &s_hook_mgr->_export;

    return 0;
}

int  hook_mgr_setting(void)
{
    return 0;
}

void hook_mgr_exit(void)
{
    mm_vfree(s_hook_mgr, sizeof(*s_hook_mgr));

    s_hook_mgr = NULL;
    g_hook     = NULL;
}

