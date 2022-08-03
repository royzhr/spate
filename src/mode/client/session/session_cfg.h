/*
 * Rodzhang
 *
 * Client Mode's session config
 */

#ifndef __SESSION_CFG_H__
#define __SESSION_CFG_H__


#include <spate_core.h>
#include <spate_config.h>
#include <spate_module.h>

/*
 * Session Module config block:
 */
typedef struct {

    spate_cfg_ipv4_t        sip;
    spate_cfg_ipv4_t        dip;

    spate_cfg_port_t        sport;
    spate_cfg_port_t        dport;

    spate_proto_e           proto;
    

    /*
     * enable session-table shuffle:
     */
    int                     table_shuffle;
    int                     table_show;
    int                     table_split_by_worker;




} session_cfg_t;





#endif /* __SESSION_CFG_H__ */

