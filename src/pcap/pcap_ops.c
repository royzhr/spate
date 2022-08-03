/*
 * Rodzhang
 *
 */

#include "pcap_ops.h"
#include "pcap_mgr.h"
#include "file/pcap_file_create.h"



static int _pcap_rx_is_match(char *pkt_data, uint16_t pkt_len)
{
    pcap_filter_t           *filter;

    if (!s_pcap_mgr->cfg.rx_enable) {
        return 0;
    }

    filter = s_pcap_mgr->rx_filter;

    if (!filter) {
        return 1;
    }

    return filter->vptr->is_match(filter, pkt_data, pkt_len);
}

static int _pcap_tx_is_match(char *pkt_data, uint16_t pkt_len)
{
    pcap_filter_t           *filter;

    if (!s_pcap_mgr->cfg.tx_enable) {
        return 0;
    }

    filter = s_pcap_mgr->tx_filter;

    if (!filter) {
        return 1;
    }

    return filter->vptr->is_match(filter, pkt_data, pkt_len);
}

const pcap_ops_t c_pcap_ops = {
    .rx_is_match = _pcap_rx_is_match,
    .tx_is_match = _pcap_tx_is_match,
    .file_create = pcap_file_create,
};
