/*
 * Rodzhang
 *
 */

#ifndef __HOST_MGR_H__
#define __HOST_MGR_H__


#include "host_export.h"

typedef struct {

    host_export_t       _export;

    /*
     * Private:
     */

} host_mgr_t;


int  host_mgr_init(void);
int  host_mgr_setting(void);
void host_mgr_exit(void);


static inline host_cfg_t *__host_cfg_block_get(void)
{
    return &g_host->cfg;
}



#endif /* __HOST_MGR_H__ */
