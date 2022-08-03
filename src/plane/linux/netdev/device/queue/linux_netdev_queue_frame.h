/*
 * Rodzhang
 *
 */

#ifndef __LINUX_NETDEV_QUEUE_FRAME_H__
#define __LINUX_NETDEV_QUEUE_FRAME_H__


#include "../linux_netdev.h"

#define LINUX_NETDEV_QUEUE_FRAME_SIZE   2048
#define LINUX_NETDEV_QUEUE_FRAME_MASK   (LINUX_NETDEV_QUEUE_FRAME_SIZE - 1)

typedef struct {

    struct tpacket_hdr      tp_hdr;

	char _padding[TPACKET_ALIGN(sizeof(struct tpacket_hdr)) - sizeof(struct tpacket_hdr)];

    char                    data[];

} linux_netdev_queue_packet_t;


typedef struct {

    union {
        linux_netdev_queue_packet_t     pkt;
        char                            _data[LINUX_NETDEV_QUEUE_FRAME_SIZE];
    };

} linux_netdev_queue_frame_t;

#define LINUX_NETDEV_PACKET_SIZE    \
    (sizeof(linux_netdev_queue_frame_t) - sizeof(linux_netdev_queue_packet_t))


static inline char *__linux_netdev_queue_frame_get_data(linux_netdev_queue_frame_t *frame)
{
    return frame->pkt.data;
}

static inline linux_netdev_queue_frame_t *__linux_netdev_queue_frame_from_data(char *data)
{
    return (linux_netdev_queue_frame_t *)
        ((intptr_t)data & (~(intptr_t)(LINUX_NETDEV_QUEUE_FRAME_MASK)));
}



#endif /* __LINUX_NETDEV_QUEUE_FRAME_H__ */
