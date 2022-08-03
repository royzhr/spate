/*
 * Rodzhang
 *
 */

#ifndef __PCAP_FILTER_H__
#define __PCAP_FILTER_H__


#include <spate_core.h>


struct _pcap_filter_s;


typedef struct {

    int (*is_match)(struct _pcap_filter_s *my, char *pkt_data, uint16_t pkt_len);

    void (*destroy)(struct _pcap_filter_s *my);

} pcap_filter_vtbl_t;


typedef struct _pcap_filter_s {

    const pcap_filter_vtbl_t    *vptr;

} pcap_filter_t;






#endif /* __PCAP_FILTER_H__ */
