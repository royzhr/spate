/*
 * Rodzhang
 *
 */

#ifndef __DPDK_CONTEXT_METHOD_H__
#define __DPDK_CONTEXT_METHOD_H__


#include "../plane_dpdk_context.h"

int  dpdk_context_constructor(plane_dpdk_context_t *ctx, uint16_t worker_id);
void dpdk_context_destructor(plane_dpdk_context_t *ctx);



#endif /* __DPDK_CONTEXT_METHOD_H__ */
