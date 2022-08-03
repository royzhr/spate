/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include "sync_imp.h"
#include "sync_factory.h"
#include "sync_method.h"


sync_t *sync_create(uint16_t worker_nr, uint16_t assist_nr)
{
    sync_imp_t              *imp;
    uint16_t                size;

    size = sizeof(sync_imp_t) + sizeof(int)*(worker_nr + assist_nr);

    imp = (sync_imp_t *)mm_vmalloc(size);

    if (!imp) {
        return NULL;
    }

    if (sync_constructor(imp, worker_nr, assist_nr, size) < 0) {
        mm_vfree(imp, size);
        return NULL;
    }

    return &imp->base;
}

