/*
 * Rodzhang
 *
 */

#ifndef __PCAP_CFG_H__
#define __PCAP_CFG_H__


#include <spate_core.h>
#include <spate_module.h>


typedef struct {

    int             enable;

    const char      *file_prefix;

    int             rx_enable;
    int             tx_enable;

    const char      *rx_filter_string;
    const char      *tx_filter_string;

} pcap_cfg_t;




#endif /* __PCAP_CFG_H__ */

