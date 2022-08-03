/*
 * Rodzhang
 *
 */

#ifndef __DPDK_CONTEXT_H__
#define __DPDK_CONTEXT_H__

#include "../plane_context.h"
#include "percpu/dpdk_percpu_export.h"
#include "dpdk_inc.h"

typedef struct {

    plane_context_t     base;

    /*
     * For dpdk's context of instance(thread)
     */
    dpdk_percpu_block_t *percpu_block;

} plane_dpdk_context_t;



#endif /* __DPDK_CONTEXT_H__ */
