/*
 * Rodzhang
 *
 */

#ifndef __NP_TCP_H__
#define __NP_TCP_H__


#include "np_types.h"

typedef struct {
	uint16_t src_port; /**< TCP source port. */
	uint16_t dst_port; /**< TCP destination port. */
	uint32_t sent_seq; /**< TX data sequence number. */
	uint32_t recv_ack; /**< RX data acknowledgment sequence number. */
	uint8_t  data_off;   /**< Data offset. */
	uint8_t  tcp_flags;  /**< TCP flags */
	uint16_t rx_win;   /**< RX flow control window. */
	uint16_t cksum;    /**< TCP checksum. */
	uint16_t tcp_urp;  /**< TCP urgent pointer, if any. */

} __attribute__((packed)) tcp_hdr_t;

#define NP_TCP_CWR_FLAG 0x80 /**< Congestion Window Reduced */
#define NP_TCP_ECE_FLAG 0x40 /**< ECN-Echo */
#define NP_TCP_URG_FLAG 0x20 /**< Urgent Pointer field significant */
#define NP_TCP_ACK_FLAG 0x10 /**< Acknowledgment field significant */
#define NP_TCP_PSH_FLAG 0x08 /**< Push Function */
#define NP_TCP_RST_FLAG 0x04 /**< Reset the connection */
#define NP_TCP_SYN_FLAG 0x02 /**< Synchronize sequence numbers */
#define NP_TCP_FIN_FLAG 0x01 /**< No more data from sender */

static __inline uint8_t __np_ipv4_hdr_len(const ipv4_hdr_t *ipv4_hdr)
{
	return (uint8_t)((ipv4_hdr->version_ihl & 0xf) * 4);
}


#endif /* __NP_TCP_H__ */

