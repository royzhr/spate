/*
 *  Rodzhang
 *
 */

#include "event_item_vtbl.h"
#include "event_item_method.h"
#include "event_item_node.h"
#include <spate_mm.h>
#include <spate_utils.h>


event_item_node_t *_event_item_node_lookup(event_item_imp_t *imp, 
        event_handler_fn handler, void *ud)
{
    event_item_node_t           *node;

    list_for_each_entry(node, &imp->head, node) {
        if (node->func == handler && node->user_data == ud) {
            return node;
        }
    }

    return NULL;
}


static int _event_item_register_handler(event_item_t *my, event_handler_fn handler, void *ud)
{
    event_item_imp_t            *imp;
    event_item_node_t           *node;

    imp = container_of(my, event_item_imp_t, base);

    node = _event_item_node_lookup(imp, handler, ud);

    if (node) {
        //already exists
        return -1;
    }

    node = event_item_node_create(handler, ud);
    if (!node) {
        return -1;
    }

    list_add_tail(&node->node, &imp->head);

    return 0;
}


static void _event_item_unregister_handler(event_item_t *my, event_handler_fn handler, void *ud)
{
    event_item_imp_t            *imp;
    event_item_node_t           *node;

    imp = container_of(my, event_item_imp_t, base);

    node = _event_item_node_lookup(imp, handler, ud);

    if (!node) {
        return;
    }

    list_del(&node->node);

    event_item_node_destroy(node);
}

static int _event_item_trigger_event(event_item_t *my, void *args)
{
    event_item_imp_t            *imp;
    event_item_node_t           *node;

    imp = container_of(my, event_item_imp_t, base);

    list_for_each_entry(node, &imp->head, node) {
        node->func(node->user_data, args);
    }

    return 0;
}

static void _event_item_destroy(event_item_t *my)
{
    event_item_imp_t            *imp;
    event_item_node_t           *node, *n;

    imp = container_of(my, event_item_imp_t, base);

    list_for_each_entry_safe(node, n, &imp->head, node) {
        list_del(&node->node);
        event_item_node_destroy(node);
    }

    event_item_destructor(imp);
    mm_vfree(imp, sizeof(*imp));
}

const event_item_vtbl_t c_event_item_vtbl = {
    .register_handler   = _event_item_register_handler,
    .unregister_handler = _event_item_unregister_handler,
    .trigger_event      = _event_item_trigger_event,
    .destroy            = _event_item_destroy,
};

