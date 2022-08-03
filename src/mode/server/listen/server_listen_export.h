/*
 * Rodzhang
 *
 */

#ifndef __SERVER_LISTEN_EXPORT_H__
#define __SERVER_LISTEN_EXPORT_H__


#include <spate_core.h>
#include "server_listen_cfg.h"


typedef struct {

    server_listen_cfg_t        cfg;

} server_listen_export_t;


extern server_listen_export_t  *g_server_listen;





static inline int __is_server_listen_proto(uint8_t proto)
{
    return g_server_listen->cfg.listen_proto_mask & proto;
}


/*
 * @port    : net byte order
 */
static inline int __is_server_listen_port(uint16_t port)
{
    return __spate_cfg_port_is_contain(&g_server_listen->cfg.listen_port, port);
}

/*
 * @ip      : net byte order
 */
static inline int __is_server_listen_ip(uint32_t ip)
{
    return __spate_cfg_ip_is_contain(&g_server_listen->cfg.listen_ip, ip);
}

/*
 *
 */
static inline int __is_server_vxlan_enable(void)
{
    return g_server_listen->cfg.vxlan_enable;
}



#endif /* __SERVER_LISTEN_EXPORT_H__ */
