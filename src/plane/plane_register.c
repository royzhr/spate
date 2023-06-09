/*
 * Rodzhang
 *
 */

#include "plane_register.h"
#include "linux/plane_linux.h"
#ifdef DPDK_ENABLE
#include "dpdk/plane_dpdk.h"
#endif

const plane_register_t *c_plane_register[] = {

    &c_plane_linux,
#ifdef DPDK_ENABLE
    &c_plane_dpdk,
#endif
    NULL
};