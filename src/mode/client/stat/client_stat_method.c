/*
 * Rodzhang
 *
 */

#include "client_stat_method.h"
#include "client_stat_vtbl.h"


int client_stat_constructor(client_stat_t *cs)
{
    memset(cs, 0, sizeof(*cs));

    cs->base.vptr = &c_client_stat_vtbl;

    return 0;
}

void client_stat_destructor(client_stat_t *cs)
{
    if (cs->history) {
        cs->history->vptr->destroy(cs->history);
        cs->history = NULL;
    }

    cs->base.vptr = NULL;
}
