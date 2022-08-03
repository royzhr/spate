/*
 * Rodzhang
 *
 */

#ifndef __VXLAN_CFG_H__
#define __VXLAN_CFG_H__


#include <spate_core.h>
#include <spate_config.h>
#include <spate_module.h>
#include <spate_net.h>


typedef struct {

    int                 enable;

    uint16_t            vni;

    spate_cfg_port_t    underlay_sport;

    spate_cfg_ipv4_t    underlay_sip;
    spate_cfg_ipv4_t    underlay_dip;

    uint8_t             underlay_dmac[NP_ETH_ALEN];

    uint8_t             overlay_smac[NP_ETH_ALEN];

    uint8_t             overlay_smac_is_setting;

} vxlan_cfg_t;




#endif /* __VXLAN_CFG_H__ */

