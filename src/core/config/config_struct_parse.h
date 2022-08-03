/*
 * Rodzhang
 *
 */

#ifndef __CONFIG_STRUCT_PARSE_H__
#define __CONFIG_STRUCT_PARSE_H__

#include <spate_core.h>
#include "config_struct.h"
#include "config_parse.h"


static inline int __config_parse_spate_ip(spate_cfg_ipv4_t *cfg_ip, const char *str)
{
    char                buf[CFG_MAX_PER_LINE+1];
    const char          *p;
    const char          *ip_str, *cnt_str;
    uint32_t            ip;
    uint16_t            cnt;
    
    p = strchr(str, '(');
    if (p) {
        strncpy(buf, str, p-str);
        buf[p-str] = 0;

        ip_str  = buf;
        cnt_str = p + 1;

    } else {
        ip_str  = str;
        cnt_str = NULL;
    }


    if (__config_parse_ipv4(&ip, ip_str) < 0) {
        LOGE("config parse ipv4 error: %s", str);
        return -1;
    }

    if (cnt_str) {
        cnt = __config_parse_uint16(p+1);
    } else {
        cnt = 1;
    }

    cfg_ip->addr = ip;
    cfg_ip->cnt  = cnt;

    return 0;
}


static inline int __config_parse_spate_port(spate_cfg_port_t *cfg_port, const char *str)
{
    char                buf[CFG_MAX_PER_LINE+1];
    const char          *p;
    const char          *port_str, *cnt_str;
    uint32_t            n;
    
    p = strchr(str, '(');
    if (p) {
        strncpy(buf, str, p-str);
        buf[p-str] = 0;

        port_str = buf;
        cnt_str  = p + 1;

    } else {
        port_str = str;
        cnt_str  = NULL;
    }

    n = __config_parse_uint32(port_str);
    if (n > 65535) {
        LOGE("config port cant large then 65535");
        return -1;
    }

    cfg_port->port = (uint16_t)n;

    if (cnt_str) {
        n = __config_parse_uint32(cnt_str);
        if (n > 65535) {
            LOGE("the count of port cant large then 65535");
            return -1;
        }
        cfg_port->cnt = (uint16_t)n;
    } else {
        cfg_port->cnt = 1;
    }

    n = cfg_port->port + cfg_port->cnt - 1;
    if (n > 65535) {
        LOGW("config the range of port error, which large then  65535, %u (%u)", 
                cfg_port->port, cfg_port->cnt);
        return -1;
    }

    return 0;
}


#endif /* __CONFIG_STRUCT_PARSE_H__ */
