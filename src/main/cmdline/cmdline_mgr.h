/*
 * Rodzhang
 *
 */

#ifndef __CMDLINE_MGR_H__
#define __CMDLINE_MGR_H__


#include "cmdline_export.h"


typedef struct {
    
    const char      *mode;

    const char      *config_file;

    const char      *plane;

    uint16_t        version : 1,
                    help    : 1,
                    show    : 1,
                    log     : 1,
                    reserve : 12;


} cmdline_args_t;



typedef struct {
    
    cmdline_export_t        _export;

    /*
     * Private
     */
    cmdline_args_t          args;

} cmdline_mgr_t;


int  cmdline_mgr_init(void);
void cmdline_mgr_exit(void);

extern cmdline_mgr_t *s_cmdline_mgr;


#endif /* __CMDLINE_MGR_H__ */
