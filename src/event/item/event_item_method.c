/*
 *  Rodzhang
 *
 */

#include "event_item_method.h"
#include "event_item_vtbl.h"



int  event_item_constructor(event_item_imp_t *imp)
{
    memset(imp, 0, sizeof(*imp));

    imp->base.vptr = &c_event_item_vtbl;

    INIT_LIST_HEAD(&imp->head);

    return 0;
}

void event_item_destructor(event_item_imp_t *imp)
{
    imp->base.vptr = NULL;
}

