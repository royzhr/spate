/*
 *  Rodzhang
 *
 */

#include "session_lookup_easy_method.h"
#include "session_lookup_easy_vtbl.h"


int  session_lookup_easy_constructor(session_lookup_easy_t *le)
{
    memset(le, 0, sizeof(*le));

    le->base.vptr = &c_session_lookup_easy_vtbl;

    return 0;
}

void session_lookup_easy_destructor(session_lookup_easy_t *le)
{
    le->base.vptr = NULL;
}


