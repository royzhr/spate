/*
 * Rodzhang
 *
 */

#ifndef __DPDK_PERCPU_EXPORT_H__
#define __DPDK_PERCPU_EXPORT_H__

#include <spate_core.h>
#include "dpdk_percpu_cfg.h"
#include "../dpdk_inc.h"

typedef struct {

    struct rte_mempool      *mbuf_pool; 

    uint16_t                id;

}__attribute__((__aligned__(128))) dpdk_percpu_block_t;



typedef struct {

    dpdk_percpu_block_t *(*get_percpu_block)(int id);

} dpdk_percpu_ops_t;


typedef struct {

    const dpdk_percpu_ops_t *ops;

    dpdk_percpu_cfg_t       cfg;

} dpdk_percpu_export_t;



#endif /* __DPDK_PERCPU_EXPORT_H__ */


