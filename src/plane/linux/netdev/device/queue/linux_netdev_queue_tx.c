/*
 * Rodzhang
 *
 */

#include "linux_netdev_queue_tx.h"
#include "../linux_netdev_pcap.h"
#include <spate_utils.h>


uint16_t linux_netdev_queue_tx_get_idle(plane_linux_netdev_queue_t *my,
        char **bufs, uint16_t *lens, uint16_t buf_nr)
{
    linux_netdev_queue_t        *queue;
    linux_netdev_ring_t         *ring;
    linux_netdev_queue_frame_t  *frame;
    uint16_t                    curr, i, nr, idle_nr;

    queue = container_of(my, linux_netdev_queue_t, base);

    ring = &queue->tx_ring;

    nr = min_of(ring->nr, buf_nr);

    idle_nr = 0;

    for (i=0; i<ring->nr && idle_nr<nr; ++i) {
        curr = (i + ring->current) % ring->nr;

        frame = &ring->frames[curr];

        if (frame->pkt.tp_hdr.tp_status == TP_STATUS_AVAILABLE) {
            /*
             * idle
             */
            bufs[idle_nr] = __linux_netdev_queue_frame_get_data(frame);
            if (lens) {
                lens[idle_nr] = LINUX_NETDEV_PACKET_SIZE;
            }

            idle_nr ++;
        }

    }

    return idle_nr;
}

uint16_t linux_netdev_queue_tx_xmit(plane_linux_netdev_queue_t *my,
        char **bufs, uint16_t *lens, uint16_t buf_nr)
{
    linux_netdev_queue_t        *queue;
    linux_netdev_ring_t         *ring;
    linux_netdev_queue_frame_t  *frame;
    int                         frame_idx;
    uint16_t                    i;

    queue = container_of(my, linux_netdev_queue_t, base);

    ring = &queue->tx_ring;

    ASSERT(buf_nr <= ring->nr);

    for (i=0; i<buf_nr; ++i) {
        frame = __linux_netdev_queue_frame_from_data(bufs[i]);

        frame_idx = frame - ring->frames;
        ASSERT(frame_idx>=0 && frame_idx<ring->nr);

        ASSERT(frame->pkt.tp_hdr.tp_status == TP_STATUS_AVAILABLE);

        frame->pkt.tp_hdr.tp_len = lens[i];

        /*
         * SMP_MP should be used here, performance is considered here, 
         * there will be no problem, because sending still needs flush.
         */
        MB();

        frame->pkt.tp_hdr.tp_status = TP_STATUS_SEND_REQUEST;
    }


    __linux_netdev_pcap(bufs, lens, i, 0);

    return buf_nr;
}



static inline uint32_t __get_need_send_size(uint16_t *lens, uint16_t tx_nr)
{
    uint32_t                    t;
    uint16_t                    i;

    t = 0;

    for (i=0; i<tx_nr; ++i) {
        t += lens[i];
    }

    return t;
}

static inline uint16_t __get_nr_from_size(uint16_t *lens, uint16_t tx_nr, uint32_t size)
{
    uint16_t                    i;
    uint32_t                    t;

    t = 0;

    for (i=0; i<tx_nr; ++i) {
        t += lens[i];
        if (t >= size) {
            return i+1;
        }
    }

    return tx_nr;
}


void linux_netdev_queue_tx_flush(plane_linux_netdev_queue_t *my, 
        uint16_t *lens, uint16_t tx_nr)
{
    linux_netdev_queue_t        *queue;
    linux_netdev_ring_t         *ring;
    int                         ret;
    uint16_t                    move_nr;
    uint32_t                    need_send;
    uint32_t                    already_send;

    queue = container_of(my, linux_netdev_queue_t, base);
    ring = &queue->tx_ring;

    need_send    = __get_need_send_size(lens, tx_nr);
    already_send = 0;

    while (already_send < need_send) {

        ret = send(queue->sock.sock_fd, NULL, 0, 0);

        if (ret < 0) {
            if (errno == EINTR) {
                continue;
            }
            break;
        } else if (ret == 0) {
            LOGE("may be wrong of TX->ring->head not match!");
            break;
        }

        already_send += ret;
    }

    if (likely(already_send > 0)) {
        move_nr = __get_nr_from_size(lens, tx_nr, already_send);

        ASSERT(tx_nr == move_nr);

        ring->current = (ring->current+move_nr) % ring->nr;
    }
}

