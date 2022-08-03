/*
 *  Rodzhang
 *
 */

#ifndef __CLIENT_STAT_HISTORY_H__
#define __CLIENT_STAT_HISTORY_H__


#include <spate_core.h>
#include "../client_stat_info.h"


struct _client_stat_history_s;

typedef struct {

    /*
     * Read:
     */
    int (*get_current_total)(struct _client_stat_history_s *my);

    const client_stat_info_t *(*get_data)(struct _client_stat_history_s *my, int idx);

    /*
     * Write:
     */
    int (*push_data)(struct _client_stat_history_s *my, const client_stat_info_t *ci);

    void (*destroy)(struct _client_stat_history_s *my);

} client_stat_history_vtbl_t;


typedef struct _client_stat_history_s {

    const client_stat_history_vtbl_t    *vptr;


} client_stat_history_t;


client_stat_history_t *client_stat_history_create(void);


#endif /* __CLIENT_STAT_HISTORY_H__ */
