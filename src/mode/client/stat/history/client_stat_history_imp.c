/*
 *  Rodzhang
 *
 */

#include "client_stat_history_imp.h"
#include "client_stat_history_method.h"
#include <spate_mm.h>


client_stat_history_t *client_stat_history_create(void)
{
    client_stat_history_imp_t   *imp;

    imp = mm_vmalloc(sizeof(*imp));
    if (!imp) {
        return NULL;
    }

    if (client_stat_history_constructor(imp) < 0) {
        mm_vfree(imp, sizeof(*imp));
        return NULL;
    }

    return &imp->base;
}


