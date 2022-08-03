/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include <spate_main.h>
#include <spate_plane.h>
#include "pcap_mgr.h"
#include "pcap_ops.h"
#include "filter/pcap_filter_create.h"


pcap_export_t   *g_pcap     = NULL;
pcap_mgr_t      *s_pcap_mgr = NULL;

int  pcap_mgr_init(void)
{
    s_pcap_mgr = mm_vmalloc(sizeof(*s_pcap_mgr));
    if (!s_pcap_mgr) {
        return -1;
    }

    memset(s_pcap_mgr, 0, sizeof(*s_pcap_mgr));

    g_pcap = &s_pcap_mgr->_export;
    g_pcap->ops = &c_pcap_ops;

    return 0;
}

int  pcap_mgr_setting(void)
{
    s_pcap_mgr->rx_filter = pcap_filter_create(s_pcap_mgr->cfg.rx_filter_string);
    s_pcap_mgr->tx_filter = pcap_filter_create(s_pcap_mgr->cfg.tx_filter_string);

    s_pcap_mgr->start_cycles = __plane_get_cycles();


    return 0;
}

void pcap_mgr_exit(void)
{
    if (s_pcap_mgr->rx_filter) {
        s_pcap_mgr->rx_filter->vptr->destroy(s_pcap_mgr->rx_filter);
        s_pcap_mgr->rx_filter = NULL;
    }
    
    if (s_pcap_mgr->tx_filter) {
        s_pcap_mgr->tx_filter->vptr->destroy(s_pcap_mgr->tx_filter);
        s_pcap_mgr->tx_filter = NULL;
    }

    mm_vfree(s_pcap_mgr, sizeof(*s_pcap_mgr));


    s_pcap_mgr = NULL;
    g_pcap     = NULL;
}

