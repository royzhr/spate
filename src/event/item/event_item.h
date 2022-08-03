/*
 *  Rodzhang
 *
 */

#ifndef __EVENT_ITEM_H__
#define __EVENT_ITEM_H__


#include "../event_export.h"

struct _event_item_s;

typedef struct {

    int  (*register_handler)(struct _event_item_s *my, event_handler_fn handler, void *ud);
    void (*unregister_handler)(struct _event_item_s *my, event_handler_fn handler, void *ud);

    int  (*trigger_event)(struct _event_item_s *my, void *args);

    void  (*destroy)(struct _event_item_s *my);

} event_item_vtbl_t;

typedef struct _event_item_s {

    const event_item_vtbl_t     *vptr;

} event_item_t;


event_item_t *event_item_create(void);


#endif /* __EVENT_ITEM_H__ */
