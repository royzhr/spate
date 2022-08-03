/*
 * Rodzhang
 *
 */

#ifndef __PLANE_UTILS_H__
#define __PLANE_UTILS_H__

#include "plane.h"

static inline uint64_t __plane_get_cycles(void)
{
    return g_plane->cycles->vptr->get_cycles(g_plane->cycles);
}

static inline uint64_t __plane_get_hz(void)
{
    return g_plane->cycles->vptr->get_hz(g_plane->cycles);
}

static inline int16_t __plane_get_worker_nr(void)
{
    return g_plane->worker_frame->vptr->get_worker_nr(g_plane->worker_frame);
}

static inline uint32_t __spate_cycles_to_usec(uint64_t cycles)
{
    uint32_t                us;
    uint64_t                hz;

    hz = __plane_get_hz();

    us = (uint32_t)((cycles*(uint64_t)1000000) / hz);

    return us;
}

static inline const uint8_t *__spate_netdev_mac_addr(void)
{
    return g_plane->netdev->info.mac_addr;
}


static inline void __plane_cycles_clean(void)
{
    if (g_plane->cycles) {
        g_plane->cycles->vptr->destroy(g_plane->cycles);
        g_plane->cycles = NULL;
    }
}

static inline void __plane_worker_frame_clean(void)
{
    if (g_plane->worker_frame) {
        g_plane->worker_frame->vptr->destroy(g_plane->worker_frame);
        g_plane->worker_frame = NULL;
    }
}

static inline void __plane_context_alloctor_clean(void)
{
    if (g_plane->context_alloctor) {
        g_plane->context_alloctor->vptr->destroy(g_plane->context_alloctor);
        g_plane->context_alloctor = NULL;
    }
}

static inline void __plane_instance_clean()
{
    if (g_plane->instance) {
        g_plane->instance->vptr->destroy(g_plane->instance);
        g_plane->instance = NULL;
    }
}


#endif /* __PLANE_UTILS_H__ */
