/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include "session_mgr.h"
#include "session_table.h"
#include "session_table_build.h"


static inline uint32_t __session_total_count(session_cfg_t *cfg)
{
    uint32_t            cnt;

    cnt = cfg->sip.cnt * cfg->dip.cnt * cfg->sport.cnt * cfg->dport.cnt;

    return cnt;
}

static inline int __session_table_alloc(session_table_t *tbl)
{
    tbl->ses = mm_vmalloc(tbl->sess_nr*sizeof(*tbl->ses));
    tbl->sis = mm_vmalloc(tbl->sess_nr*sizeof(*tbl->sis));

    if (!tbl->ses || !tbl->sis) {
        return -1;
    }

    memset(tbl->ses, 0, tbl->sess_nr*sizeof(*tbl->ses));
    memset(tbl->sis, 0, tbl->sess_nr*sizeof(*tbl->sis));

    return 0;
}

static inline void __session_table_free(session_table_t *tbl)
{
    mm_vfree(tbl->ses, tbl->sess_nr*sizeof(*tbl->ses));
    mm_vfree(tbl->sis, tbl->sess_nr*sizeof(*tbl->sis));

    tbl->ses = NULL;
    tbl->sis = NULL;
}



int session_table_init(void)
{
    return 0;
}

int session_table_setting(void)
{
    session_table_t     *tbl;
    session_cfg_t       *cfg;

    cfg = __session_cfg_block_get();
    tbl = __session_table_get();

    tbl->sess_nr = __session_total_count(cfg);
    if (!tbl->sess_nr) {
        LOGE("session table element is ZERO! error");
        return -1;
    }

    if (__session_table_alloc(tbl) < 0) {
        LOGE("session table alloc memory failed: session count %u", tbl->sess_nr);
        return -1;
    }

    LOGD("session table alloc %d", tbl->sess_nr);

    if (session_table_build(tbl, cfg) < 0) {
        return -1;
    }

    return 0;
}

void session_table_exit(void)
{
    session_table_t     *tbl;

    tbl = __session_table_get();

    __session_table_free(tbl);
}


