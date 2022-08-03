/*
 * Rodzhang
 *
 */


#include "pcap_module.h"
#include "pcap_mgr.h"
#include "pcap_cfg_ops.h"


static int _pcap_module_init(void)
{
    if (pcap_mgr_init() < 0) {
        return -1;
    }

    return 0;
}

static int _pcap_module_setting(void)
{
    if (pcap_mgr_setting() < 0) {
        return -1;
    }

    return 0;
}

static void _pcap_module_exit(void)
{
    pcap_mgr_exit();
}

const module_class_t c_pcap_module = {
    .module_name    = "pcap",
    .cfg_ops        = &c_pcap_cfg_ops,
    .module_init    = _pcap_module_init,
    .module_setting = _pcap_module_setting,
    .module_exit    = _pcap_module_exit,
};


