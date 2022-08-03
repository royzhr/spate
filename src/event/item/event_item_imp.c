/*
 *  Rodzhang
 *
 */

#include "event_item_imp.h"
#include <spate_mm.h>
#include "event_item_method.h"


event_item_t *event_item_create(void)
{
    event_item_imp_t        *imp;

    imp = mm_vmalloc(sizeof(*imp));
    if (!imp) {
        return NULL;
    }

    if (event_item_constructor(imp) < 0) {
        mm_vfree(imp, sizeof(*imp));
        return NULL;
    }
    
    return &imp->base;
}

