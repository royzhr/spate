/*
 * Rodzhang
 *
 */

#include "io_log.h"
#include "io_main_mgr.h"



int  io_log_init(void)
{
    FILE        *f;

    f = fopen("_spate.log", "wt");
    if (!f) {
        return -1;
    }

    s_io_mgr->log = f;

    return 0;
}

void io_log_exit(void)
{
    fclose(s_io_mgr->log);
    s_io_mgr->log = NULL;
}

