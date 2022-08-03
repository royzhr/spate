/*
 * Rodzhang
 *
 */

#ifndef __NP_IPV4_H__
#define __NP_IPV4_H__

#include "np_types.h"

typedef struct {
	uint8_t  version_ihl;		/**< version and header length */
	uint8_t  type_of_service;	/**< type of service */
	uint16_t total_length;	/**< length of packet */
	uint16_t packet_id;		/**< packet ID */
	uint16_t fragment_offset;	/**< fragmentation offset */
	uint8_t  time_to_live;		/**< time to live */
	uint8_t  next_proto_id;		/**< protocol ID */
	uint16_t hdr_checksum;	/**< header checksum */
	uint32_t src_addr;		/**< source address */
	uint32_t dst_addr;		/**< destination address */
} __attribute__((packed)) ipv4_hdr_t;



#endif /* __NP_IPV4_H__ */
