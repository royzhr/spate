/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_config.h>
#include <spate_utils.h>
#include "dpdk_netdev_cfg.h"
#include "dpdk_netdev_cfg_ops.h"
#include "dpdk_netdev_mgr.h"


static inline dpdk_netdev_cfg_t *__get_dpdk_netdev_cfg()
{
    dpdk_netdev_mgr_t       *mgr;

    mgr = __get_dpdk_netdev_mgr();

    return &mgr->_export.cfg;
}


static inline void __dpdk_netdev_cfg_default(dpdk_netdev_cfg_t *cfg)
{
    cfg->name = NULL;

    cfg->rx_desc = PLANE_NETDEV_RX_DESC;
    cfg->tx_desc = PLANE_NETDEV_TX_DESC;
    
    cfg->is_promiscuous = 1;
}


static void _dpdk_netdev_cfg_begin(void)
{
    dpdk_netdev_cfg_t       *cfg;

    cfg = __get_dpdk_netdev_cfg();

    __dpdk_netdev_cfg_default(cfg);
}

static int _dpdk_netdev_cfg_finish(void)
{
    dpdk_netdev_cfg_t       *cfg;

    cfg = __get_dpdk_netdev_cfg();

    if (!is_power_of_2(cfg->rx_desc)) {
        LOGW("config dpdk_netdev_rx_desc must be power of 2, now is %u, set to default", 
                cfg->rx_desc);
        cfg->rx_desc = PLANE_NETDEV_RX_DESC;
    }

    if (!is_power_of_2(cfg->tx_desc)) {
        LOGW("config dpdk_netdev_tx_desc must be power of 2, now is %u, set to default", 
                cfg->tx_desc);
        cfg->tx_desc = PLANE_NETDEV_TX_DESC;
    }

    if (!cfg->name) {
        LOGW("dpdk netdev name has no setting in config file");
        return -1;
    }

    return 0;
}

static int _dpdk_netdev_cfg_parse_line(const char *key, const char *val)
{
    dpdk_netdev_cfg_t       *cfg;

    cfg = __get_dpdk_netdev_cfg();

    if (!strcmp(key, "dpdk.netdev.name")) {
        cfg->name = strdup(val);
        return 1;

    } else if (!strcmp(key, "dpdk.netdev.rx_desc")) {
        cfg->rx_desc = __config_parse_uint16(val);
        return 1;

    } else if (!strcmp(key, "dpdk.netdev.tx_desc")) {
        cfg->tx_desc = __config_parse_uint16(val);
        return 1;

    } else if (!strcmp(key, "dpdk.netdev.promiscuous")) {
        cfg->is_promiscuous = __config_parse_bool(val);
        return 1;

    }

    return 0;
}

const module_cfg_ops_t c_dpdk_netdev_cfg_ops = {
    .begin      = _dpdk_netdev_cfg_begin,
    .finish     = _dpdk_netdev_cfg_finish,
    .parse_line = _dpdk_netdev_cfg_parse_line,
};
