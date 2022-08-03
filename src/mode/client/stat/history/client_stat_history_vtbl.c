/*
 *  Rodzhang
 *
 */

#include "client_stat_history_vtbl.h"
#include "client_stat_history_method.h"
#include <spate_mm.h>
#include <spate_utils.h>


static int _client_stat_history_get_current_total(client_stat_history_t *my)
{
    client_stat_history_imp_t       *imp;

    imp = container_of(my, client_stat_history_imp_t, base);

    return imp->curr_len;
}

static const client_stat_info_t *_client_stat_history_get_data(client_stat_history_t *my, int idx)
{
    client_stat_history_imp_t       *imp;

    imp = container_of(my, client_stat_history_imp_t, base);

    if (idx<0 || idx>=imp->curr_len) {
        return NULL;
    }

    return &imp->infos[idx];
}

static int _client_stat_history_push_data(client_stat_history_t *my, 
        const client_stat_info_t *ci)
{
    client_stat_history_imp_t       *imp;
    client_stat_info_t              *dst;

    imp = container_of(my, client_stat_history_imp_t, base);

    if (imp->curr_len >= imp->max_len) {
        return -1;
    }

    dst = &imp->infos[imp->curr_len];

    imp->curr_len++;

    client_stat_info_copy(dst, ci);

    //LOGW("push data: %lu", ci->traffic.tx_pkts);

    return 0;
}


static void _client_stat_history_destroy(client_stat_history_t *my)
{
    client_stat_history_imp_t       *imp;

    imp = container_of(my, client_stat_history_imp_t, base);

    client_stat_history_destructor(imp);

    mm_vfree(imp, sizeof(*imp));
}

const client_stat_history_vtbl_t c_client_stat_history_vtbl = {
    .get_current_total = _client_stat_history_get_current_total,
    .get_data          = _client_stat_history_get_data,
    .push_data         = _client_stat_history_push_data,
    .destroy           = _client_stat_history_destroy,
};


