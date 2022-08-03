/*
 * Rodzhang
 *
 */

#ifndef __DPDK_NETDEV_LOOKUP_H__
#define __DPDK_NETDEV_LOOKUP_H__

#include <stdint.h>

/*
 * Lookup port_id by pci_slot_name
 *
 */
int dpdk_netdev_lookup(const char *netdev_name, uint16_t *port_id);




#endif /* __DPDK_NETDEV_LOOKUP_H__ */

