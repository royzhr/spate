/*
 *  Rodzhang
 *
 */

#include "event_ops.h"
#include "event_mgr.h"


static int _event_register_handler(event_type_e ev, event_handler_fn handler, void *ud)
{
    event_item_t        *item;

    ASSERT(ev>=0 && ev<EVENT_END);

    item = s_event_mgr->items[ev];

    ASSERT(item);

    return item->vptr->register_handler(item, handler, ud);
}

static void _event_unregister_handler(event_type_e ev, event_handler_fn handler, void *ud)
{
    event_item_t        *item;

    ASSERT(ev>=0 && ev<EVENT_END);

    item = s_event_mgr->items[ev];

    ASSERT(item);

    item->vptr->unregister_handler(item, handler, ud);
}

static int _event_trigger_event(event_type_e ev, void *args)
{
    event_item_t        *item;

    ASSERT(ev>=0 && ev<EVENT_END);

    item = s_event_mgr->items[ev];

    ASSERT(item);

    return item->vptr->trigger_event(item, args);
}

const event_ops_t c_event_ops = {
    .register_handler   = _event_register_handler,
    .unregister_handler = _event_unregister_handler,
    .trigger_event      = _event_trigger_event,
};

