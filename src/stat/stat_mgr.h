/*
 * Rodzhang
 *
 */

#ifndef __STAT_MGR_H__
#define __STAT_MGR_H__


#include <spate_core.h>
#include "stat.h"
#include "stat_export.h"
#include <pthread.h>

typedef struct {

    stat_export_t   _export;

    pthread_t       stat_thread;

} stat_mgr_t;



int  stat_mgr_init(void);
int  stat_mgr_setting(void);
void stat_mgr_exit(void);


extern stat_mgr_t   *s_stat_mgr;


static inline stat_cfg_t *__stat_cfg_block_get(void)
{
    return &s_stat_mgr->_export.stat->cfg;
}





#endif /* __STAT_MGR_H__ */

