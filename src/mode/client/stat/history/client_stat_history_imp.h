/*
 *  Rodzhang
 *
 */

#ifndef __CLIENT_STAT_HISTORY_IMP_H__
#define __CLIENT_STAT_HISTORY_IMP_H__


#include "client_stat_history.h"

typedef struct {

    client_stat_history_t       base;

    /*
     * Private:
     */

    uint16_t                    max_len;
    uint16_t                    curr_len;

    client_stat_info_t          *infos;


} client_stat_history_imp_t;



#endif /* __CLIENT_STAT_HISTORY_IMP_H__ */

