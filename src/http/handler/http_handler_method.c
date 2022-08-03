/*
 *  Rodzhang
 *
 */

#include "http_handler_method.h"
#include "http_handler_vtbl.h"


int  http_handler_constructor(http_handler_imp_t *imp)
{
    memset(imp, 0, sizeof(*imp));

    imp->base.vptr = &c_http_handler_vtbl;

    return 0;
}

void http_handler_destructor(http_handler_imp_t *imp)
{
    imp->base.vptr = NULL;
}


