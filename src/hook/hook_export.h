/*
 * Rodzhang
 *
 */

#ifndef __HOOK_EXPORT_H__
#define __HOOK_EXPORT_H__


#include <spate_core.h>
#include "hook_cfg.h"

typedef struct {

    hook_cfg_t      cfg;

} hook_export_t;

extern hook_export_t    *g_hook;




#endif /* __HOOK_EXPORT_H__ */
