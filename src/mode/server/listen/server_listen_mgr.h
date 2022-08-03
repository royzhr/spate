/*
 * Rodzhang
 *
 */

#ifndef __SERVER_LISTEN_MGR_H__
#define __SERVER_LISTEN_MGR_H__


#include "server_listen_export.h"
#include "server_listen_cfg.h"

typedef struct {

    server_listen_export_t     _export;

    /*
     * Private:
     */

} server_listen_mgr_t;


int  server_listen_mgr_init(void);
int  server_listen_mgr_setting(void);
void server_listen_mgr_exit(void);


/*
 * Private (Only used in this module)
 */
extern server_listen_mgr_t *s_server_listen_mgr;


static inline server_listen_cfg_t *__server_listen_cfg_block_get(void)
{
    return &g_server_listen->cfg;
}





#endif /* __SERVER_LISTEN_MGR_H__ */
