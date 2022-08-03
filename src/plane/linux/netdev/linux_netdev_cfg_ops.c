/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_config.h>
#include <spate_utils.h>
#include "linux_netdev_cfg.h"
#include "linux_netdev_cfg_ops.h"
#include "linux_netdev_mgr.h"


static inline linux_netdev_cfg_t *__get_linux_netdev_cfg()
{
    linux_netdev_mgr_t       *mgr;

    mgr = __get_linux_netdev_mgr();

    return &mgr->_export.cfg;
}


static inline void __linux_netdev_cfg_default(linux_netdev_cfg_t *cfg)
{
    cfg->name = NULL;

    cfg->rx_desc = PLANE_NETDEV_RX_DESC;
    cfg->tx_desc = PLANE_NETDEV_TX_DESC;

    cfg->is_bypass_qdisc = 0;
}


static void _linux_netdev_cfg_begin(void)
{
    linux_netdev_cfg_t       *cfg;

    cfg = __get_linux_netdev_cfg();

    __linux_netdev_cfg_default(cfg);
}

static int _linux_netdev_cfg_finish(void)
{
    linux_netdev_cfg_t       *cfg;

    cfg = __get_linux_netdev_cfg();

    if (!is_power_of_2(cfg->rx_desc)) {
        LOGW("config linux_netdev_rx_desc must be power of 2, now is %u, set to default", 
                cfg->rx_desc);
        cfg->rx_desc = PLANE_NETDEV_RX_DESC;
    }

    if (!is_power_of_2(cfg->tx_desc)) {
        LOGW("config linux_netdev_tx_desc must be power of 2, now is %u, set to default", 
                cfg->tx_desc);
        cfg->tx_desc = PLANE_NETDEV_TX_DESC;
    }

    if (!cfg->name) {
        LOGE("linux netdev name has no set is config file");
        return -1;
    }

    return 0;
}

static int _linux_netdev_cfg_parse_line(const char *key, const char *val)
{
    linux_netdev_cfg_t       *cfg;

    cfg = __get_linux_netdev_cfg();

    if (!strcmp(key, "linux.netdev.name")) {
        cfg->name = strdup(val);
        return 1;

    } else if (!strcmp(key, "linux.netdev.rx_desc")) {
        cfg->rx_desc = __config_parse_uint16(val);
        return 1;

    } else if (!strcmp(key, "linux.netdev.tx_desc")) {
        cfg->tx_desc = __config_parse_uint16(val);
        return 1;

    } else if (!strcmp(key, "linux.netdev.bypass_qdisc")) {
        cfg->is_bypass_qdisc = __config_parse_bool(val);
        return 1;

    }

    return 0;
}

const module_cfg_ops_t c_linux_netdev_cfg_ops = {
    .begin      = _linux_netdev_cfg_begin,
    .finish     = _linux_netdev_cfg_finish,
    .parse_line = _linux_netdev_cfg_parse_line,
};
