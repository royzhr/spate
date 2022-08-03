/*
 * Rodzhang
 *
 */


#include <spate_mm.h>
#include "server_stat.h"
#include "server_stat_method.h"

stat_t *server_stat_create(void)
{
    server_stat_t       *ss;

    ss = mm_vmalloc(sizeof(*ss));
    if (!ss) {
        return NULL;
    }

    if (server_stat_constructor(ss) < 0) {
        mm_vfree(ss, sizeof(*ss));
        return NULL;
    }

    return &ss->base;
}
