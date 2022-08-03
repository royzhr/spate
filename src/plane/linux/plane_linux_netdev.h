/*
 * Rodzhang
 *
 */

#ifndef __PLANE_LINUX_NETDEV_H__
#define __PLANE_LINUX_NETDEV_H__


#include "../plane_netdev.h"



struct _plane_linux_netdev_queue_s;

typedef struct {

    /*
     * TX
     */

    /*
     * @buf_nr: The number of the idler-bufs that needed
     */
    uint16_t (*tx_get_idle)(struct _plane_linux_netdev_queue_s *my, 
            char **bufs, uint16_t *lens, uint16_t buf_nr);

    uint16_t (*tx_xmit)(struct _plane_linux_netdev_queue_s *my, 
            char **bufs, uint16_t *lens, uint16_t buf_nr);

    /*
     * @tx_nr  : Corresponding to the kernel's packet_increment_head func
     * If u want to know why, see kernel souce
     */
    void (*tx_flush)(struct _plane_linux_netdev_queue_s *my,
            uint16_t *lens, uint16_t tx_nr);


    /*
     * RX
     */
    uint16_t (*rx_get_pkts)(struct _plane_linux_netdev_queue_s *my, 
            char **bufs, uint16_t *lens, uint16_t buf_nr);

    uint16_t (*rx_clean)(struct _plane_linux_netdev_queue_s *my, 
            char **bufs, uint16_t buf_nr);


    void (*rx_wait)(struct _plane_linux_netdev_queue_s *my, uint32_t timeout_us);

    /*
     * Utils
     */
    uint16_t (*get_id)(struct _plane_linux_netdev_queue_s *my);

    void (*destroy)(struct _plane_linux_netdev_queue_s *my);

} plane_linux_netdev_queue_vtbl_t;


typedef struct _plane_linux_netdev_queue_s {

    const plane_linux_netdev_queue_vtbl_t   *vptr;

} plane_linux_netdev_queue_t;



typedef struct _plane_linux_netdev_s {
    
    plane_netdev_t              base;

    int                         if_index;
    uint16_t                    queue_nr;

    plane_linux_netdev_queue_t  *queues[SPATE_MAX_WORKER];

} plane_linux_netdev_t;



#endif /* __PLANE_LINUX_NETDEV_H__ */

