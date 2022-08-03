/*
 * Rodzhang
 *
 */

#include "dpdk_netdev_factory.h"
#include "dpdk_netdev_lookup.h"
#include "dpdk_netdev_method.h"
#include <spate_mm.h>


plane_netdev_t *dpdk_netdev_factory(dpdk_netdev_cfg_t *cfg)
{
    plane_dpdk_netdev_t         *dev;
    uint16_t                    port_id;

    if (dpdk_netdev_lookup(cfg->name, &port_id) < 0) {
        LOGE("cant find dev name=%s", cfg->name);
        return NULL;
    }

    dev = mm_vmalloc(sizeof(*dev));
    if (!dev) {
        return NULL;
    }

    if (dpdk_netdev_constructor(dev, port_id) < 0) {
        mm_vfree(dev, sizeof(*dev));
        return NULL;
    }

    return &dev->base;
}
