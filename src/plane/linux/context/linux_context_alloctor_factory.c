/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include "linux_context_alloctor_factory.h"
#include "linux_context_factory.h"
#include "../../plane_context_alloctor_method.h"



static plane_context_t *_linux_context_alloctor_alloc_context(
        __UNUSED__ plane_context_alloctor_t *my, uint16_t worker_id)
{
    return linux_context_factory(worker_id);
}

static void _linux_context_alloctor_destroy(plane_context_alloctor_t *my)
{
    plane_context_alloctor_destructor(my);

    mm_vfree(my, sizeof(*my));
}

static const plane_context_alloctor_vtbl_t c_plane_linux_context_alloctor = {
    .alloc_context = _linux_context_alloctor_alloc_context,
    .destroy       = _linux_context_alloctor_destroy,
};


plane_context_alloctor_t *plane_linux_context_alloctor_factory(void)
{
    plane_context_alloctor_t        *alloctor;

    alloctor = mm_vmalloc(sizeof(*alloctor));

    if (plane_context_alloctor_constructor(alloctor, &c_plane_linux_context_alloctor ) < 0) {
        mm_vfree(alloctor, sizeof(*alloctor));
        return NULL;
    }

    return alloctor;
}


