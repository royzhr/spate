/*
 * Rodzhang
 *
 */

#ifndef __STAT_CFG_H__
#define __STAT_CFG_H__


#include <spate_core.h>


/*
 * Base stat infomation
 */
typedef struct {

    uint16_t            flush_wait_time;

    uint16_t            max_history_time;

    int                 worker_enable;

} stat_cfg_t;




#endif /* __STAT_CFG_H__ */
