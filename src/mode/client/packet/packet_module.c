/*
 * Rodzhang
 *
 */

#include "packet_module.h"
#include "packet_mgr.h"
#include "packet_cfg_ops.h"


static int _packet_module_init(void)
{
    if (packet_mgr_init() < 0) {
        return -1;
    }

    return 0;
}

static int _packet_module_setting(void)
{
    if (packet_mgr_setting() < 0) {
        return -1;
    }

    return 0;
}

static void _packet_module_exit(void)
{
    packet_mgr_exit();
}

const module_class_t c_packet_module = {
    .module_name    = "packet",
    .cfg_ops        = &c_packet_cfg_ops,
    .module_init    = _packet_module_init,
    .module_setting = _packet_module_setting,
    .module_exit    = _packet_module_exit,
};


