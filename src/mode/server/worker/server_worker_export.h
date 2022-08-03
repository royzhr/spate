/*
 * Rodzhang
 *
 */

#ifndef __SERVER_WORKER_EXPORT_H__
#define __SERVER_WORKER_EXPORT_H__


#include <spate_core.h>
#include "../stat/server_stat_info.h"

typedef const server_stat_info_t *(*extend_server_stat_fn)(void *ud);

typedef struct {
    
    uint16_t (*get_worker_nr)(void);

    const server_stat_info_t *(*get_server_stat_info)(uint16_t worker_id);

    /*
     * Get extend-offload's stat, such as ebpf
     */
    const server_stat_info_t *(*get_server_extend_stat_info)(void);

    /*
     * From Hook , such as ebpf-offload:
     */
    int  (*register_server_extend_stat_handler)(extend_server_stat_fn fn, void *ud);
    void (*unregister_server_extend_stat_handler)(extend_server_stat_fn fn, void *ud);

} server_worker_ops_t;

typedef struct {

    const server_worker_ops_t   *ops;

} server_worker_export_t;

extern server_worker_export_t *g_server_worker;




#endif /* __SERVER_WORKER_EXPORT_H__ */
