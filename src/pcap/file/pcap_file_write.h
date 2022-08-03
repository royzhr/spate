/*
 * Rodzhang
 *
 */

#ifndef __PCAP_FILE_WRITE_H__
#define __PCAP_FILE_WRITE_H__



#include <spate_core.h>


int pcap_file_write_header(FILE *fp);

int pcap_file_write_packet(FILE *fp, char *pkt_data, uint16_t pkt_len, uint32_t sec, uint32_t us);




#endif /* __PCAP_FILE_WRITE_H__ */
