/*
 * Rodzhang
 *
 * The file format of *.pcap 
 */

#ifndef __PCAP_FILE_FORMAT_H__
#define __PCAP_FILE_FORMAT_H__


#include <spate_core.h>

typedef struct {
	uint32_t    magic;      /* 0xA1B2C3D4 for sec&us */
	uint16_t    version_major;
	uint16_t    version_minor;
	int         thiszone;	/* gmt to local correction; this is always 0 */
	uint32_t    sigfigs;	/* accuracy of timestamps; this is always 0 */
	uint32_t    snaplen;	/* max length saved portion of each pkt */
	uint32_t    linktype;	/* data link type (LINKTYPE_*) */
} pcap_file_header_t;


typedef struct {
    uint32_t    sec;
    uint32_t    us;
	uint32_t    caplen;	/* length of portion present */
	uint32_t    len;	/* length of this packet (off wire) */
} pcap_pkthdr_t;



#endif /* __PCAP_FILE_FORMAT_H__ */
