/*
 * Rodzhang
 *
 */

#ifndef __TICK_MGR_H__
#define __TICK_MGR_H__


#include "tick_export.h"
#include <pthread.h>


typedef struct {

    tick_export_t   _export;

    /*
     * Private:
     */

    uint32_t        ticks;

    pthread_t       thread;


    /*
     * Notify: 
     */
    void (*notify_fn)(void);
    uint32_t        notify_tick;

} tick_mgr_t;


int  tick_mgr_init(void);
int  tick_mgr_setting(void);
void tick_mgr_exit(void);
 

/*
 * Private:
 */
extern tick_mgr_t   *s_tick_mgr;


#endif /* __TICK_MGR_H__ */

