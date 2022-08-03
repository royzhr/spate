/*
 * Rodzhang
 *
 */

#ifndef __CLIENT_STAT_H__
#define __CLIENT_STAT_H__



#include <spate_stat.h>
#include "client_stat_cfg.h"
#include "client_stat_info.h"
#include "history/client_stat_history.h"



typedef struct {

    /*
     * Base
     */
    stat_t                  base;

    /*
     * For client only:
     */
    
    client_stat_history_t   *history;

    client_stat_cfg_t       client_cfg;


    client_stat_info_t      info_now;
    client_stat_info_t      info_last;

} client_stat_t;


stat_t *client_stat_create(void);





#endif /* __CLIENT_STAT_H__ */
