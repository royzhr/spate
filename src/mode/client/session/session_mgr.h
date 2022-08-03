/*
 * Rodzhang
 *
 */

#ifndef __SESSION_MGR_H__
#define __SESSION_MGR_H__


#include "session_export.h"
#include "session_cfg.h"
#include "session_table.h"
#include "session_graceful.h"
#include "lookup/session_lookup.h"


typedef struct {

    session_export_t        _export;

    /*
     * Private:
     */

    session_table_t         table;

    session_graceful_t      graceful;


    session_lookup_t        *lookup;

} session_mgr_t;


int  session_mgr_init(void);
int  session_mgr_setting(void);
void session_mgr_exit(void);



/*
 * Private (Only used in this module)
 */
extern session_mgr_t *s_session_mgr;



static inline session_cfg_t *__session_cfg_block_get(void)
{
    return &g_session->cfg;
}

static inline session_table_t *__session_table_get(void)
{
    return &s_session_mgr->table;
}


#endif /* __SESSION_MGR_H__ */


