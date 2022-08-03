/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_INCLUDE_H__
#define __EBPF_INCLUDE_H__


#include <stdint.h>
#include <string.h>
#include <linux/bpf.h>
#include <linux/in.h>
#include <linux/if.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/if_tunnel.h>
#include <linux/pkt_cls.h>
#include <linux/types.h>
#include <linux/socket.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_packet.h>

#include <iproute2/bpf_elf.h>


#ifndef __inline
# define __inline inline __attribute__((always_inline))
#endif






#endif /* __EBPF_INCLUDE_H__ */
