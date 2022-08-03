/*
 *  Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include "session_lookup_easy.h"
#include "session_lookup_easy_method.h"


session_lookup_t *session_lookup_easy_create(void)
{
    session_lookup_easy_t       *le;

    le = mm_vmalloc(sizeof(*le));
    if (!le) {
        return NULL;
    }

    if (session_lookup_easy_constructor(le) < 0) {
        mm_vfree(le, sizeof(*le));
        return NULL;
    }

    return &le->base;
}


