/*
 * Rodzhang
 *
 */

#ifndef __DPDK_INC_H__
#define __DPDK_INC_H__


/*
 * DPDK-Lib
 */

#include <rte_config.h>
#include <rte_mbuf.h>
#include <rte_common.h>
#include <rte_log.h>
#include <rte_malloc.h>
#include <rte_eal.h>
#include <rte_launch.h>
#include <rte_atomic.h>
#include <rte_cycles.h>
#include <rte_prefetch.h>
#include <rte_lcore.h>
#include <rte_per_lcore.h>
#include <rte_branch_prediction.h>
#include <rte_interrupts.h>
#include <rte_random.h>
#include <rte_debug.h>
#include <rte_ethdev.h>
#include <rte_mempool.h>
#include <rte_debug.h>


/*
 * Spate config of RTE
 */
#define SPATE_MEMPOOL_CACHE_SIZE    256

#define DPDK_PACKET_MBUF(pkt_data, pkt_len, mbuf)       \
    pkt_data = (char *)mbuf->buf_addr + mbuf->data_off; \
    pkt_len  = mbuf->data_len;




#endif /* __DPDK_INC_H__ */
