/*
 *  Rodzhang
 *
 */

#ifndef __OS_MGR_H__
#define __OS_MGR_H__


#include "os_export.h"

typedef struct {

    os_export_t     _export;

    /*
     * Private
     */
    void (*sig_process)(int sig);

} os_mgr_t;


extern os_mgr_t *s_os_mgr;

int  os_mgr_init();
void os_mgr_exit();


#endif /* __OS_MGR_H__ */
