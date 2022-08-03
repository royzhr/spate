/*
 * Rodzhang
 *
 */

#ifndef __PCAP_MGR_H__
#define __PCAP_MGR_H__


#include "pcap_export.h"
#include "pcap_cfg.h"
#include "filter/pcap_filter.h"


typedef struct {


    pcap_export_t   _export;

    /*
     * Private: 
     */
    pcap_cfg_t      cfg;

    pcap_filter_t   *rx_filter;
    pcap_filter_t   *tx_filter;

    uint64_t        start_cycles;

} pcap_mgr_t;




int  pcap_mgr_init(void);
int  pcap_mgr_setting(void);
void pcap_mgr_exit(void);


extern pcap_mgr_t   *s_pcap_mgr;


static inline pcap_cfg_t *__pcap_cfg_block_get(void)
{
    return &s_pcap_mgr->cfg;
}




#endif /* __PCAP_MGR_H__ */
