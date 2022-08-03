/*
 * Rodzhang
 *
 */

#include "io_redirect.h"
#include "io_main_mgr.h"


int  io_redirect_init(void)
{
    s_io_mgr->stdout = stdout;
    s_io_mgr->stdin  = stdin;

    //stdout = s_io_mgr->log;
    s_io_mgr->log = stdout;

    return 0;
}

void io_redirect_exit(void)
{
    //stdout = s_io_mgr->stdout;
}


