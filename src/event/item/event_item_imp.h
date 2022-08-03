/*
 *  Rodzhang
 *
 */

#ifndef __EVENT_ITEM_IMP_H__
#define __EVENT_ITEM_IMP_H__


#include "event_item.h"
#include <utils/list.h>



typedef struct {

    event_item_t        base;

    struct list_head    head;

} event_item_imp_t;



#endif /* __EVENT_ITEM_IMP_H__ */
