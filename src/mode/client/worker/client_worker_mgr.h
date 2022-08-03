/*
 * Rodzhang
 *
 */

#ifndef __CLIENT_WORKER_MGR_H__
#define __CLIENT_WORKER_MGR_H__


#include "client_worker_export.h"
#include "instance/client_instance_context.h"

typedef struct {

    extend_client_stat_fn       func;
    void                        *user_data;

} client_extend_stat_handler_t;

typedef struct {

    client_worker_export_t          _export;

    /*
     * Private
     */
    client_instance_context_t       *contexts;

    uint16_t                        worker_nr;

    client_extend_stat_handler_t    extend_stat_handler;


} client_worker_mgr_t;


int  client_worker_mgr_init(void);
int  client_worker_mgr_setting(void);
void client_worker_mgr_exit(void);



/*
 * Private (Only used in this module)
 */
extern client_worker_mgr_t  *s_client_worker_mgr;



#endif /* __CLIENT_WORKER_MGR_H__ */

