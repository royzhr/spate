/*
 * Rodzhang
 *
 */

#ifndef __HOST_EXPORT_H__
#define __HOST_EXPORT_H__


#include <spate_core.h>
#include "host_cfg.h"


typedef struct {

    int (*on_worker_init)(uint16_t worker_id);

} host_ops_t;


typedef struct {
    
    const host_ops_t    *ops;

    host_cfg_t          cfg;

} host_export_t;


extern host_export_t    *g_host;



static inline int __host_is_arp_enable(void)
{
    return g_host->cfg.arp_enable;
}

static inline int __host_is_icmp_enable(void)
{
    return g_host->cfg.icmp_enable;
}

/*
 * @ip      : net byte order
 */
static inline int __host_is_my_ip(uint32_t ip)
{
    return __spate_cfg_ip_is_contain(&g_host->cfg.host_ip, ip);
}



#endif /* __HOST_EXPORT_H__ */

