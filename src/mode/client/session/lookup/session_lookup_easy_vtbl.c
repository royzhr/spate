/*
 *  Rodzhang
 *
 */

#include <spate_mm.h>
#include "session_lookup_easy_vtbl.h"
#include "session_lookup_easy_method.h"
#include <spate_utils.h>



static inline int __session_easy_lookup_linear(session_lookup_easy_t *le, uint32_t *sess_idx, 
        uint32_t sip, uint32_t dip, uint16_t sport, uint16_t dport)
{
    uint32_t                i, nr;
    session_table_t         *table;
    session_engress_t       *ses, *curr;
    
    table = &s_session_mgr->table;
    ses   = table->ses;

    nr = table->sess_nr;

    for (i=0; i<nr; i++) {
        curr = ses + i;

        if (curr->sip==sip && curr->dip==dip && curr->sport==sport && curr->dport==dport) {
            *sess_idx = i;
            return 0;
        }
    }

    return -1;
}

static inline int __session_easy_lookup_without_shuffle(session_lookup_easy_t *le, 
        uint32_t *sess_idx, uint32_t sip, uint32_t dip, uint16_t sport, uint16_t dport)
{
    session_table_t         *table;
    uint16_t                si, di, sp, dp;
    uint32_t                idx;
    session_cfg_t           *cfg;
    
    cfg   = &g_session->cfg;
    table = &s_session_mgr->table;

    si = sip - cfg->sip.addr;
    di = dip - cfg->dip.addr;
    dp = dport - cfg->dport.port;
    sp = sport - cfg->sport.port;

    if (si>=cfg->sip.cnt || di>=cfg->dip.cnt || dp>=cfg->dport.cnt || sp>=cfg->sport.cnt) {
        return -1;
    }

    idx = 0;
    idx += sp * (cfg->dport.cnt * cfg->dip.cnt * cfg->sip.cnt);
    idx += dp * (cfg->dip.cnt * cfg->sip.cnt);
    idx += di * (cfg->sip.cnt);
    idx += si;

    *sess_idx = idx;

    {
        session_engress_t       *curr;

        curr = table->ses + idx;

        ASSERT(curr->sip==sip && curr->dip==dip && curr->sport==sport && curr->dport==dport);
    }

    return 0;
}

static int _session_lookup_easy_lookup(session_lookup_t *my, uint32_t *sess_idx, 
        uint32_t sip, uint32_t dip, uint16_t sport, uint16_t dport)
{
    session_lookup_easy_t       *le;

    le = container_of(my, session_lookup_easy_t, base);

    if (!g_session->cfg.table_shuffle) {
        return __session_easy_lookup_without_shuffle(le, sess_idx, sip, dip, sport, dport);
    } else {
        return __session_easy_lookup_linear(le, sess_idx, sip, dip, sport, dport);
    }

    return -1;
}
 
static void _session_lookup_easy_destroy(session_lookup_t *my)
{
    session_lookup_easy_t       *le;

    le = container_of(my, session_lookup_easy_t, base);

    session_lookup_easy_destructor(le);

    mm_vfree(le, sizeof(*le));
}

const session_lookup_vtbl_t c_session_lookup_easy_vtbl = {
    .lookup  = _session_lookup_easy_lookup,
    .destroy = _session_lookup_easy_destroy,
};

