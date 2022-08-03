/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include "main_mgr.h"
#include "main_ops.h"


main_export_t   *g_main     = NULL;
main_mgr_t      *s_main_mgr = NULL;




int  main_mgr_init(void)
{
    s_main_mgr = mm_vmalloc(sizeof(*s_main_mgr));

    memset(s_main_mgr, 0, sizeof(*s_main_mgr));
    g_main = &s_main_mgr->_export;

    g_main->quit_sig    = 0;
    g_main->force_quit  = 0;
    g_main->pcap_enable = 0;

    g_main->ops = &c_main_ops;

    return 0;
}

void main_mgr_exit(void)
{
    g_main->ops = NULL;

    mm_vfree(s_main_mgr, sizeof(*s_main_mgr));

    s_main_mgr = NULL;
    g_main     = NULL;
}

