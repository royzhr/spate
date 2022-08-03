/*
 * Rodzhang
 *
 */

#ifndef __CLIENT_WORKER_EXPORT_H__
#define __CLIENT_WORKER_EXPORT_H__


#include <spate_core.h>
#include "../stat/client_stat_info.h"


typedef const client_stat_info_t *(*extend_client_stat_fn)(void *ud);

typedef struct {
    
    uint16_t (*get_worker_nr)(void);

    /*
     * Get worker's stat
     */
    const client_stat_info_t *(*get_client_stat_info)(uint16_t worker_id);

    /*
     * Get extend-offload's stat, such as ebpf
     */
    const client_stat_info_t *(*get_client_extend_stat_info)(void);

    /*
     * From Hook , such as ebpf-offload:
     */
    int  (*register_client_extend_stat_handler)(extend_client_stat_fn fn, void *ud);
    void (*unregister_client_extend_stat_handler)(extend_client_stat_fn fn, void *ud);

} client_worker_ops_t;

typedef struct {

    const client_worker_ops_t   *ops;

} client_worker_export_t;

extern client_worker_export_t *g_client_worker;


#endif /* __CLIENT_WORKER_EXPORT_H__ */


