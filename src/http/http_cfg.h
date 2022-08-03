/*
 *  Rodzhang
 *
 */

#ifndef __HTTP_CFG_H__
#define __HTTP_CFG_H__


#include <spate_core.h>
#include <spate_config.h>


typedef struct {

    int                     enable;

    spate_cfg_ipv4_t        listen_ip;
    spate_cfg_port_t        listen_port;

} http_cfg_t;



#endif /* __HTTP_CFG_H__ */

