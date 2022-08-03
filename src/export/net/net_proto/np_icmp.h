/*
 * Rodzhang
 *
 */

#ifndef __NP_ICMP_H__
#define __NP_ICMP_H__


#include "np_types.h"

typedef struct {

	uint8_t  icmp_type;     /* ICMP packet type. */
	uint8_t  icmp_code;     /* ICMP packet code. */
	uint16_t icmp_cksum;  /* ICMP packet checksum. */
	uint16_t icmp_ident;  /* ICMP packet identifier. */
	uint16_t icmp_seq_nb; /* ICMP packet sequence number. */

} __attribute__((packed)) icmp_hdr_t;

/* ICMP packet types */
#define NP_IP_ICMP_ECHO_REPLY   0
#define NP_IP_ICMP_ECHO_REQUEST 8


#endif /* __NP_ICMP_H__ */

