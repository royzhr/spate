/*
 *  Rodzhang
 *
 */

#ifndef __EVENT_ITEM_NODE_H__
#define __EVENT_ITEM_NODE_H__


#include "event_item_imp.h"


typedef struct {
    
    struct list_head    node;

    event_handler_fn    func;

    void                *user_data;

} event_item_node_t;


event_item_node_t *event_item_node_create(event_handler_fn fn, void *ud);
void event_item_node_destroy(event_item_node_t *node);


#endif /* __EVENT_ITEM_NODE_H__ */
