/*
 * Rodzhang
 *
 */

#ifndef __PLANE_NETDEV_H__
#define __PLANE_NETDEV_H__


#include <spate_core.h>
#include <spate_net_proto.h>

struct _plane_netdev_s;

typedef struct {

    void (*destroy)(struct _plane_netdev_s *my);

    uint16_t (*tx_packets)(struct _plane_netdev_s *my, char **pkts, uint16_t *lens, 
            uint16_t pkt_nr, uint16_t worker_id);

} plane_netdev_vtbl_t;


typedef struct {

    uint8_t         mac_addr[NP_ETH_ALEN];

} netdev_info_t;



typedef struct _plane_netdev_s {

    const plane_netdev_vtbl_t       *vptr;

    netdev_info_t                   info;

} plane_netdev_t;


static inline uint16_t __plane_netdev_tx_packet(plane_netdev_t *dev, 
        char *pkt, uint16_t len, uint16_t worker_id)
{
    char            *pkts[1];
    uint16_t        lens [1];

    pkts[0] = pkt;
    lens[0] = len;

    return dev->vptr->tx_packets(dev, pkts, lens, 1, worker_id);
}


/*
 * Default value of rx-tx desc size :
 */
#define PLANE_NETDEV_RX_DESC   4096
#define PLANE_NETDEV_TX_DESC   4096



#endif /* __PLANE_NETDEV_H__ */

