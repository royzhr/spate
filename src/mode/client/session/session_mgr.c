/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include "session_mgr.h"
#include "session_ops.h"
#include "session_table.h"

session_mgr_t       *s_session_mgr = NULL;
session_export_t    *g_session = NULL;


int  session_mgr_init(void)
{
    s_session_mgr = mm_vmalloc(sizeof(*s_session_mgr));

    if (!s_session_mgr) {
        return -1;
    }

    memset(s_session_mgr, 0, sizeof(*s_session_mgr));

    g_session = &s_session_mgr->_export;

    if (session_table_init() < 0) {
        return -1;
    }
    if (session_graceful_init() < 0) {
        return -1;
    }

    g_session->ops = &c_session_ops;

    return 0;
}

int  session_mgr_setting(void)
{
    if (session_table_setting() < 0) {
        return -1;
    }
    if (session_graceful_setting() < 0) {
        return -1;
    }

    s_session_mgr->lookup = session_lookup_create();

    return 0;
}

void session_mgr_exit(void)
{
    g_session->ops = NULL;

    if (s_session_mgr->lookup) {
        s_session_mgr->lookup->vptr->destroy(s_session_mgr->lookup);
        s_session_mgr->lookup = NULL;
    }

    session_graceful_exit();
    session_table_exit();

    mm_vfree(s_session_mgr, sizeof(*s_session_mgr));

    s_session_mgr = NULL;
    g_session     = NULL;
}


