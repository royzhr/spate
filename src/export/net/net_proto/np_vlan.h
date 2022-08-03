/*
 * Rodzhang
 *
 */

#ifndef __NP_VLAN_H__
#define __NP_VLAN_H__


#include "np_types.h"


typedef struct {
	
    uint16_t vlan_tci; /**< Priority (3) + CFI (1) + Identifier Code (12) */
	uint16_t eth_proto;/**< Ethernet type of encapsulated frame. */

} __attribute__((packed)) vlan_hdr_t;


#endif /* __NP_VLAN_H__ */

