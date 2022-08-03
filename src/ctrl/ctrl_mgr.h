/*
 * Rodzhang
 *
 */

#ifndef __CTRL_MGR_H__
#define __CTRL_MGR_H__


#include "ctrl_export.h"
#include <pthread.h>


typedef struct {

    ctrl_export_t       _export;

    /*
     * Private
     */

    pthread_t           ctrl_thread;

} ctrl_mgr_t;

int  ctrl_mgr_init(void);
int  ctrl_mgr_setting(void);
void ctrl_mgr_exit(void);


extern ctrl_mgr_t   *s_ctrl_mgr;



#endif /* __CTRL_MGR_H__ */

