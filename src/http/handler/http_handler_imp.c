/*
 *  Rodzhang
 *
 */

#include "http_handler_imp.h"
#include "http_handler_method.h"
#include <spate_mm.h>


http_handler_t *http_handler_create(void)
{
    http_handler_imp_t          *imp;

    imp = mm_vmalloc(sizeof(*imp));

    if (!imp) {
        return NULL;
    }

    if (http_handler_constructor(imp) < 0) {
        mm_vfree(imp, sizeof(*imp));
        return NULL;
    }

    return &imp->base;

}


