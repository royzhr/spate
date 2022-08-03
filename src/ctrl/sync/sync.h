/*
 * Rodzhang
 *
 */

#ifndef __SYNC_H__
#define __SYNC_H__


#include <spate_core.h>

struct _sync_s;

typedef struct {


    /*
     * All thread come to report and wait to start at same time.
     */
    void (*report_on_sync_wait)(struct _sync_s *my, int report_id);

    int  (*is_all_report)(struct _sync_s *my);

    void (*wake_all_waiter)(struct _sync_s *my);

    void (*destroy)(struct _sync_s *my);

} sync_vtbl_t;

typedef struct _sync_s {

    const sync_vtbl_t      *vptr;

    //volatile int    start;
} sync_t;





#endif /* __SYNC_H__ */ 
