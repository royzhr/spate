/*
 * Rodzhang
 *
 */

#ifndef __SERVER_LISTEN_CFG_H__
#define __SERVER_LISTEN_CFG_H__


#include <spate_core.h>
#include <spate_config.h>
#include <spate_module.h>


/*
 * server_listen module config block
 *  -- config of server mode
 *
 */
typedef struct {
    spate_cfg_ipv4_t        listen_ip;
    spate_cfg_port_t        listen_port;


    uint8_t                 listen_proto_mask;

    int                     vxlan_enable;

    spate_cfg_ipv4_t        vxlan_vtep_ip;

} server_listen_cfg_t;



#endif /* __SERVER_LISTEN_CFG_H__ */


