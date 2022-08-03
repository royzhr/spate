/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include "linux_filter_imp.h"
#include "linux_filter_factory.h"
#include "linux_filter_method.h"


linux_filter_t *linux_filter_factory(void)
{
    linux_filter_imp_t      *imp;

    imp = mm_vmalloc(sizeof(*imp));
    if (!imp) {
        return NULL;
    }


    if (linux_filter_constructor(imp) < 0) {
        mm_vfree(imp, sizeof(*imp));
        return NULL;
    }

    return &imp->base;
}

