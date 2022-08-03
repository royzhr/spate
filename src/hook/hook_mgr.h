/*
 * Rodzhang
 *
 */

#ifndef __HOOK_MGR_H__
#define __HOOK_MGR_H__


#include "hook_export.h"

typedef struct {

    hook_export_t       _export;

    /*
     * Private:
     */

} hook_mgr_t;

int  hook_mgr_init(void);
int  hook_mgr_setting(void);
void hook_mgr_exit(void);


static inline hook_cfg_t *__hook_cfg_block_get(void)
{
    return &g_hook->cfg;
}


#endif /* __HOOK_MGR_H__ */

