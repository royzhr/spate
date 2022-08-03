/*
 * Rodzhang
 *
 */

#ifndef __DPDK_CYCLES_H__
#define __DPDK_CYCLES_H__

#include <spate_core.h>
#include "../../plane_cycles.h"

typedef struct {

    plane_cycles_t      base;

    uint64_t            cycles_per_second;

} plane_dpdk_cycles_t;



#endif /* __DPDK_CYCLES_H__ */
