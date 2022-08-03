/*
 * Rodzhang
 *
 */

#ifndef __PCAP_FILE_H__
#define __PCAP_FILE_H__


#include <spate_core.h>


struct _pcap_file_s;

typedef struct {
    
    int  (*fsave)   (struct _pcap_file_s *my, uint64_t cycles, char *pkt_data, uint16_t pkt_len);

    void (*fflush)  (struct _pcap_file_s *my);

    void (*destroy) (struct _pcap_file_s *my);

} pcap_file_vtbl_t;

typedef struct _pcap_file_s {

    const pcap_file_vtbl_t      *vptr;

} pcap_file_t;



#endif /* __PCAP_FILE_H__ */
