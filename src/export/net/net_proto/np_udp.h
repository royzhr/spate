/*
 * Rodzhang
 *
 */

#ifndef __NP_UDP_H__
#define __NP_UDP_H__

#include "np_types.h"

typedef struct {
	uint16_t src_port;    /**< UDP source port. */
	uint16_t dst_port;    /**< UDP destination port. */
	uint16_t dgram_len;   /**< UDP datagram length */
	uint16_t dgram_cksum; /**< UDP datagram checksum */
} __attribute__((packed)) udp_hdr_t;


typedef struct {
	uint32_t vx_flags; /**< flag (8) + Reserved (24). */
	uint32_t vx_vni;   /**< VNI (24) + Reserved (8). */
} __attribute__((packed)) vxlan_hdr_t;



#endif /* __NP_UDP_H__ */
