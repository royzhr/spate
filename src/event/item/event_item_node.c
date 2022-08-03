/*
 *  Rodzhang
 *
 */

#include "event_item_node.h"
#include <spate_mm.h>


event_item_node_t *event_item_node_create(event_handler_fn fn, void *ud)
{
    event_item_node_t       *node;

    node = mm_vmalloc(sizeof(*node));

    if (!node) {
        return NULL;
    }

    memset(node, 0, sizeof(*node));

    node->func      = fn;
    node->user_data = ud;

    return node;
}

void event_item_node_destroy(event_item_node_t *node)
{
    mm_vfree(node, sizeof(*node));
}

