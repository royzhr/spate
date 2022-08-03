/*
 * Rodzhang
 *
 * This file provides the function of cksum, derived from dpdk.
 */

#ifndef __NP_CKSUM_H__
#define __NP_CKSUM_H__

#include "net_proto.h"


/*
 * This function has a loop, ebpf cannot be used !!!!
 *
 */
static __inline uint32_t __np_raw_cksum_calc(const void *buf, uint32_t len, uint32_t sum)
{
	/* workaround gcc strict-aliasing warning */
	typedef uint16_t __attribute__((__may_alias__)) u16_p;
	const u16_p *u16_buf = (const u16_p *)(buf);

	while (len >= (sizeof(*u16_buf) * 4)) {
		sum += u16_buf[0];
		sum += u16_buf[1];
		sum += u16_buf[2];
		sum += u16_buf[3];
		len -= sizeof(*u16_buf) * 4;
		u16_buf += 4;
	}
	while (len >= sizeof(*u16_buf)) {
		sum += *u16_buf;
		len -= sizeof(*u16_buf);
		u16_buf += 1;
	}

	/* if length is in odd bytes */
	if (len == 1) {
		uint16_t left = 0;
		*(uint8_t *)&left = *(const uint8_t *)u16_buf;
		sum += left;
	}

	return sum;
}

static __inline uint16_t __np_raw_cksum_reduce(uint32_t sum)
{
	sum = ((sum & 0xffff0000) >> 16) + (sum & 0xffff);
	sum = ((sum & 0xffff0000) >> 16) + (sum & 0xffff);
	return (uint16_t)sum;
}

static __inline uint16_t __np_raw_cksum(const void *buf, uint32_t len)
{
	uint32_t sum;

	sum = __np_raw_cksum_calc(buf, len, 0);
	return __np_raw_cksum_reduce(sum);
}

static __inline uint16_t __np_ipv4_phdr_cksum(const ipv4_hdr_t *ipv4_hdr)
{
	struct ipv4_psd_header {
		uint32_t src_addr; /* IP address of source host. */
		uint32_t dst_addr; /* IP address of destination host. */
		uint8_t  zero;     /* zero. */
		uint8_t  proto;    /* L4 protocol type. */
		uint16_t len;      /* L4 length. */
	} psd_hdr;

	uint32_t        l3_len;

	psd_hdr.src_addr = ipv4_hdr->src_addr;
	psd_hdr.dst_addr = ipv4_hdr->dst_addr;
	psd_hdr.zero = 0;
	psd_hdr.proto = ipv4_hdr->next_proto_id;
    l3_len = __ntohs(ipv4_hdr->total_length);
    psd_hdr.len = __ntohs((uint16_t)(l3_len - __np_ipv4_hdr_len(ipv4_hdr)));

	return __np_raw_cksum(&psd_hdr, sizeof(psd_hdr));
}

/*
 * Used to calc udp&tcp 's cksum
 *
 */
static __inline uint16_t __np_ipv4_udptcp_cksum(const ipv4_hdr_t *ipv4_hdr, 
        const void *l4_hdr, uint16_t l4_len)
{
	uint32_t cksum;

	cksum = __np_raw_cksum(l4_hdr, l4_len);
	cksum += __np_ipv4_phdr_cksum(ipv4_hdr);

	cksum = ((cksum & 0xffff0000) >> 16) + (cksum & 0xffff);
	cksum = (~cksum) & 0xffff;
	/*
	 * Per RFC 768:If the computed checksum is zero for UDP,
	 * it is transmitted as all ones
	 * (the equivalent in one's complement arithmetic).
	 */
	if (cksum == 0 && ipv4_hdr->next_proto_id == IPPROTO_UDP)
		cksum = 0xffff;

	return (uint16_t)cksum;
}

/*
 * Used to calc IP 's cksum
 *
 */
static __inline uint16_t __np_ipv4_cksum(const ipv4_hdr_t *ipv4_hdr)
{
	uint16_t cksum;
	cksum = __np_raw_cksum(ipv4_hdr, __np_ipv4_hdr_len(ipv4_hdr));
	return (uint16_t)~cksum;
}

#endif /* __NP_CKSUM_H__ */
