
/*
 * Rodzhang
 *
 */

#include "server_stat_method.h"
#include "server_stat_vtbl.h"


int server_stat_constructor(server_stat_t *ss)
{
    memset(ss, 0, sizeof(*ss));

    ss->base.vptr = &c_server_stat_vtbl;

    return 0;
}

void server_stat_destructor(server_stat_t *ss)
{

    ss->base.vptr = NULL;

}
