/*
 * Rodzhang
 *
 */

#ifndef __IO_MAIN_MGR_H__
#define __IO_MAIN_MGR_H__


#include "io_main_export.h"

typedef struct {

    io_export_t     _export;

    /*
     * Private:
     */
    FILE            *stdout;
    FILE            *stdin;
    FILE            *log;

} io_mgr_t;


int  io_mgr_init(void);
void io_mgr_exit(void);


/*
 * Private:
 */
extern io_mgr_t *s_io_mgr;



#endif /* __IO_MAIN_MGR_H__ */
