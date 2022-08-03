/*
 *  Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include "http_accept_imp.h"
#include "http_accept_method.h"


http_accept_t *http_accept_create(const http_cfg_t *cfg)
{
    http_accept_imp_t       *imp;

    imp = mm_vmalloc(sizeof(*imp));
    if (!imp) {
        return NULL;
    }

    if (http_accept_constructor(imp) < 0) {
        mm_vfree(imp, sizeof(*imp));
        return NULL;
    }

    return &imp->base;
}


