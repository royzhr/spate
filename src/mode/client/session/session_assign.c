/*
 * Rodzhang
 *
 */

#include "session_assign.h"



static int _session_assign_all_to_worker(session_roll_t *sr, uint16_t worker_id, 
        uint16_t worker_nr)
{
    uint32_t                session_nr;

    session_nr = s_session_mgr->table.sess_nr;

    sr->sess_idx_begin = 0;
    sr->sess_idx_end   = session_nr;
    sr->sess_idx_curr  = sr->sess_idx_begin; 

    return 0;
}

static int _session_assign_split_to_worker(session_roll_t *sr, uint16_t worker_id,
        uint16_t worker_nr)
{
    uint32_t                session_nr;
    uint32_t                session_per_worker;
    uint32_t                begin, end;

    session_nr = s_session_mgr->table.sess_nr;

    session_per_worker = (session_nr + worker_nr - 1) / worker_nr;

    begin = session_per_worker * worker_id;
    end   = begin+session_per_worker > session_nr ? session_nr : begin+session_per_worker;

    sr->sess_idx_begin = begin;
    sr->sess_idx_end   = end;
    sr->sess_idx_curr  = sr->sess_idx_begin; 

    return 0;
}


int session_assign_to_worker(session_roll_t *sr, uint16_t worker_id, uint16_t worker_nr)
{
    if (g_session->cfg.table_split_by_worker) {

        return _session_assign_split_to_worker(sr, worker_id, worker_nr);
    } else {

        return _session_assign_all_to_worker(sr, worker_id, worker_nr);
    }

}




