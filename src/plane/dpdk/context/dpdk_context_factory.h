/*
 * Rodzhang
 *
 */

#ifndef __DPDK_CONTEXT_FACTORY_H__
#define __DPDK_CONTEXT_FACTORY_H__


#include "../plane_dpdk_context.h"

plane_context_t *dpdk_context_factory(uint16_t worker_id);


#endif /* __DPDK_CONTEXT_FACTORY_H__ */
