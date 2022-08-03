/*
 * Rodzhang
 *
 */

#include "sync_method.h"
#include "sync_vtbl.h"
#include <string.h>


int  sync_constructor(sync_imp_t *imp, uint16_t worker_nr, uint16_t assist_nr, uint16_t size)
{
    memset(imp, 0, size);

    imp->size      = size;
    imp->worker_nr = worker_nr;
    imp->assist_nr = assist_nr;

    imp->workers   = &imp->report_boards[assist_nr];

    imp->base.vptr = &c_sync_vtbl;

    return 0;
}

void sync_destructor(sync_imp_t *imp)
{
    imp->base.vptr = NULL;
}

