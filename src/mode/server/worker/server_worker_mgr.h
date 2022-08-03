/*
 * Rodzhang
 *
 */

#ifndef __SERVER_WORKER_MGR_H__
#define __SERVER_WORKER_MGR_H__


#include "server_worker_export.h"
#include "instance/server_instance_context.h"

typedef struct {

    extend_server_stat_fn       func;
    void                        *user_data;

} server_extend_stat_handler_t;

typedef struct {

    server_worker_export_t          _export;

    /*
     * Private
     */
    server_instance_context_t       *contexts;

    uint16_t                        worker_nr;

    server_extend_stat_handler_t    extend_stat_handler;

} server_worker_mgr_t;


int  server_worker_mgr_init(void);
int  server_worker_mgr_setting(void);
void server_worker_mgr_exit(void);


extern server_worker_mgr_t     *s_server_worker_mgr;




#endif /* __SERVER_WORKER_MGR_H__ */
