/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include "packet_mgr.h"
#include "packet_ops.h"


packet_export_t    *g_packet      = NULL;
packet_mgr_t       *s_packet_mgr  = NULL;


int  packet_mgr_init(void)
{
    s_packet_mgr = mm_vmalloc(sizeof(*s_packet_mgr));

    if (!s_packet_mgr) {
        return -1;
    }

    memset(s_packet_mgr, 0, sizeof(*s_packet_mgr));

    g_packet = &s_packet_mgr->_export;
    g_packet->ops = &c_packet_ops;

    return 0;
}

int  packet_mgr_setting(void)
{
    return 0;
}

void packet_mgr_exit(void)
{
    mm_vfree(s_packet_mgr, sizeof(*s_packet_mgr));

    s_packet_mgr = NULL;
    g_packet     = NULL;
}

