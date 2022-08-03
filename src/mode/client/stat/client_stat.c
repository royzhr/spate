/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include "client_stat.h"
#include "client_stat_method.h"


stat_t *client_stat_create(void)
{
    client_stat_t       *cs;

    cs = mm_vmalloc(sizeof(*cs));
    if (!cs) {
        return NULL;
    }

    if (client_stat_constructor(cs) < 0) {
        mm_vfree(cs, sizeof(*cs));
        return NULL;
    }

    return &cs->base;
}


