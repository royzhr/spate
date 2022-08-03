/*
 *  Rodzhang
 *
 */

#ifndef __EVENT_MGR_H__
#define __EVENT_MGR_H__


#include "event_export.h"
#include "item/event_item.h"


typedef struct {

    event_export_t      _export;

    /*
     * Private:
     */
    event_item_t        *items[EVENT_END];

} event_mgr_t;

extern event_mgr_t     *s_event_mgr;

int  event_mgr_init(void);
int  event_mgr_setting(void);
void event_mgr_exit(void);

#endif /* __EVENT_MGR_H__ */
