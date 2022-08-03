/*
 *  Rodzhang
 *
 */

#include "session_lookup.h"
#include "session_lookup_easy.h"


void session_lookup_test(session_lookup_t *lookup)
{
    session_table_t         *table;
    session_engress_t       *curr;
    int                     ret;
    uint32_t                sess_idx;
    uint32_t                i;
    
    table = &s_session_mgr->table;
    

    for (i=0; i<table->sess_nr; ++i) {
        
        curr = table->ses + i;

        ret = lookup->vptr->lookup(lookup, &sess_idx, curr->sip, 
                curr->dip, curr->sport, curr->dport);

        ASSERT(ret == 0);

        ASSERT(sess_idx == i);
    }

    LOGW("Test Lokup OK : %u", table->sess_nr);
}



session_lookup_t *session_lookup_create(void)
{
    session_lookup_t        *lookup;

    lookup = NULL;

    if (!g_session->cfg.table_shuffle || s_session_mgr->table.sess_nr<128) {
        lookup = session_lookup_easy_create();
    } else {
        LOGE("You shuffle the session table, Now Need Todo Hash to search session"); 
    }

    /*
    if (lookup) {
        session_lookup_test(lookup);
    }
    */

    return lookup;
}



