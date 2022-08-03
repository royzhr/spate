/*
 *  Rodzhang
 *
 */

#ifndef __EVENT_EXPORT_H__
#define __EVENT_EXPORT_H__


#include <spate_core.h>

typedef enum {
    EVENT_NOTHING = 0,
    EVENT_PPS_CHANGE,
    EVENT_QUIT,

    EVENT_END,
} event_type_e;


typedef int (*event_handler_fn)(void *user_data, void *args);

typedef struct {

    int  (*register_handler)(event_type_e ev, event_handler_fn handler, void *user_data);
    void (*unregister_handler)(event_type_e ev, event_handler_fn handler, void *user_data);

    int  (*trigger_event)(event_type_e ev, void *args);

} event_ops_t;


typedef struct {

    const event_ops_t   *ops;

} event_export_t;

extern event_export_t *g_event;



#endif /* __EVENT_EXPORT_H__ */
