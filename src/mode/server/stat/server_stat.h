/*
 * Rodzhang
 *
 */

#ifndef __SERVER_STAT_H__
#define __SERVER_STAT_H__



#include <spate_stat.h>
#include "server_stat_info.h"


typedef struct {

    /*
     * Base
     */
    stat_t              base;

    /*
     * For server only:
     */
    server_stat_info_t  info_now;
    server_stat_info_t  info_last;

} server_stat_t;


stat_t *server_stat_create(void);






#endif /* __SERVER_STAT_H__ */
