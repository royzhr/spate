/*
 *  Rodzhang
 *
 */

#include "event_mgr.h"
#include "event_ops.h"
#include <spate_mm.h>


event_export_t  *g_event     = NULL;
event_mgr_t     *s_event_mgr = NULL;


static int _event_items_init(void)
{
    int                 i;
    event_item_t        *item;

    for (i=0; i<EVENT_END; ++i) {
        item = event_item_create();
        if (!item) {
            return -1;
        }

        s_event_mgr->items[i] = item;
    }

    return 0;
}

static void _event_items_exit(void)
{
    int                 i;
    event_item_t        *item;

    for (i=0; i<EVENT_END; ++i) {
        
        item = s_event_mgr->items[i];

        item->vptr->destroy(item);

        s_event_mgr->items[i] = NULL;
    }
}


int  event_mgr_init(void)
{
    s_event_mgr = mm_vmalloc(sizeof(*s_event_mgr));

    if (!s_event_mgr) {
        return -1;
    }

    memset(s_event_mgr, 0, sizeof(*s_event_mgr));

    g_event = &s_event_mgr->_export;
    g_event->ops = &c_event_ops;

    if (_event_items_init() < 0) {
        return -1;
    }

    return 0;
}

int  event_mgr_setting(void)
{
    return 0;
}

void event_mgr_exit(void)
{
    _event_items_exit();

    mm_vfree(s_event_mgr, sizeof(*s_event_mgr));

    s_event_mgr = NULL;
    g_event     = NULL;
}
