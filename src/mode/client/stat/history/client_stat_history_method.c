/*
 *  Rodzhang
 *
 */

#include "client_stat_history_method.h"
#include "client_stat_history_vtbl.h"
#include <spate_mm.h>
#include <spate_stat.h>


int  client_stat_history_constructor(client_stat_history_imp_t *imp)
{
    uint16_t                max;

    memset(imp, 0, sizeof(*imp));

    imp->base.vptr = &c_client_stat_history_vtbl;

    max = g_stat->stat->cfg.max_history_time;

    imp->max_len = max;

    imp->infos = mm_vmalloc(sizeof(client_stat_info_t)*imp->max_len);
    if (!imp->infos) {
        return -1;
    }

    imp->curr_len = 0;

    return 0;
}

void client_stat_history_destructor(client_stat_history_imp_t *imp)
{
    mm_vfree(imp->infos, sizeof(client_stat_info_t)*imp->max_len);
    imp->infos = NULL;

    imp->base.vptr = NULL;
}


