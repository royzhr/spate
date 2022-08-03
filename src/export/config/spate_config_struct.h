/*
 *  Rodzhang
 *
 * This .h file is used by both spate and ebpf-prog.
 */

#ifndef __SPATE_CONFIG_STRUCT_H__
#define __SPATE_CONFIG_STRUCT_H__


#include <stdint.h>

/*
 * Config Session's ipv4 addr infomation
 */
typedef struct {

    /*
     * host byte order
     */
    uint32_t        addr;

    uint16_t        cnt;


} spate_cfg_ipv4_t;


typedef struct {

    /*
     * host byte order
     */
    uint16_t        port;

    uint16_t        cnt;

} spate_cfg_port_t;


static __inline void __spate_cfg_ipv4_invalid_to_default(spate_cfg_ipv4_t *cfg_ip)
{
    if (!cfg_ip->cnt) {
        cfg_ip->cnt = 1;
    }
}

static __inline void __spate_cfg_port_invalid_to_default(spate_cfg_port_t *cfg_port)
{
    if (!cfg_port->cnt) {
        cfg_port->cnt = 1;
    }
}

/*
 * @port_net    : net byte order
 */
static __inline int __spate_cfg_port_is_contain(const spate_cfg_port_t *cfg_port, uint16_t port_net)
{
    uint16_t            port;

    if (cfg_port->port == 0) {
        return 1;
    }

    port = __ntohs(port_net);

    if (port >= cfg_port->port && port < cfg_port->port+cfg_port->cnt) {
        return 1;
    }

    return 0;
}

/*
 * @ip_host  : host byte order
 */
static __inline int __spate_cfg_ip_is_contain_on_host(const spate_cfg_ipv4_t *cfg_ip, 
        uint32_t ip_host)
{
    if (cfg_ip->cnt == 0) {
        return 0;
    }

    if (cfg_ip->addr == 0 && cfg_ip->cnt == 1) {
        return 1;
    }

    if (ip_host >= cfg_ip->addr && ip_host < cfg_ip->addr+cfg_ip->cnt) {
        return 1;
    }

    return 0;
}

/*
 * @ip_net   : net byte order
 */
static __inline int __spate_cfg_ip_is_contain(const spate_cfg_ipv4_t *cfg_ip, uint32_t ip_net)
{
    return __spate_cfg_ip_is_contain_on_host(cfg_ip, __ntohl(ip_net));
}










#endif /* __SPATE_CONFIG_STRUCT_H__ */
