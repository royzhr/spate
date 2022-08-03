/*
 * Rodzhang
 *
 */

#ifndef __PCAP_EXPORT_H__
#define __PCAP_EXPORT_H__


#include <spate_core.h>
#include "file/pcap_file.h"


typedef struct {

    /*
     * Return value:
     * 0    : Not match
     * 1    : match
     */
    int (*rx_is_match)(char *pkt_data, uint16_t pkt_len);
    int (*tx_is_match)(char *pkt_data, uint16_t pkt_len);

    pcap_file_t *(*file_create)(uint16_t worker_id);

} pcap_ops_t;


typedef struct {

    const pcap_ops_t    *ops;

} pcap_export_t;

extern pcap_export_t    *g_pcap;



static inline int __pcap_is_match(int is_rx, char *pkt_data, uint16_t pkt_len)
{
    if (is_rx) {
        return g_pcap->ops->rx_is_match(pkt_data, pkt_len);
    } else {
        return g_pcap->ops->tx_is_match(pkt_data, pkt_len);
    }
}


#endif /* __PCAP_EXPORT_H__ */

