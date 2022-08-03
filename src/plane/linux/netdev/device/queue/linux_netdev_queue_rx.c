/*
 * Rodzhang
 *
 */

#include "linux_netdev_queue_rx.h"
#include "../linux_netdev_pcap.h"
#include <spate_utils.h>

uint16_t linux_netdev_queue_rx_get_pkts(plane_linux_netdev_queue_t *my,
        char **bufs, uint16_t *lens, uint16_t buf_nr)
{
    linux_netdev_queue_t        *queue;
    linux_netdev_ring_t         *ring;
    linux_netdev_queue_frame_t  *frame;
    uint16_t                    curr, i, nr, rx_nr;

    queue = container_of(my, linux_netdev_queue_t, base);

    ring = &queue->rx_ring;

    nr = min_of(ring->nr, buf_nr);

    rx_nr = 0;

    for (i=0; i<ring->nr && rx_nr<nr; ++i) {
        curr = (i + ring->current) % ring->nr;

        frame = &ring->frames[curr];

        if (frame->pkt.tp_hdr.tp_status & TP_STATUS_USER) {
            /*
             * recv
             */
            bufs[rx_nr] = (char *)frame + frame->pkt.tp_hdr.tp_mac;
            lens[rx_nr] = frame->pkt.tp_hdr.tp_len;

            rx_nr ++;
        } else if (frame->pkt.tp_hdr.tp_status & TP_STATUS_COPY) {
            LOGW("err at TP_COPY");
        } else if (frame->pkt.tp_hdr.tp_status & TP_STATUS_LOSING) {
            LOGW("err at TP_LOSING");
        } else {
            break;
        }

    }

    if (rx_nr) {
        ring->current = (ring->current + rx_nr) % ring->nr;

    }

    // LOGD("buf_nr:%d, rx_nr:%d,", buf_nr, rx_nr);

    __linux_netdev_pcap(bufs, lens, rx_nr, 1);

    return rx_nr;
}

uint16_t linux_netdev_queue_rx_clean(plane_linux_netdev_queue_t *my, 
        char **bufs, uint16_t buf_nr)

{
    linux_netdev_queue_t        *queue;
    linux_netdev_ring_t         *ring;
    linux_netdev_queue_frame_t  *frame;
    int                         frame_idx;
    int                         i;

    queue = container_of(my, linux_netdev_queue_t, base);

    ring = &queue->rx_ring;

    ASSERT(buf_nr <= ring->nr);

    //for (i=0; i<buf_nr; ++i) {
    for (i=buf_nr-1; i>=0; i--) {
        frame = __linux_netdev_queue_frame_from_data(bufs[i]);

        frame_idx = frame - ring->frames;
        ASSERT(frame_idx>=0 && frame_idx<ring->nr);

        ASSERT(frame->pkt.tp_hdr.tp_status & TP_STATUS_USER);

        frame->pkt.tp_hdr.tp_status = TP_STATUS_KERNEL;
    }

    SMP_MB();

    return buf_nr;
}


/*
 * If you want to use ppoll ,maust define __USE_GNU 
 */
#define _GUN_SOURCE
#define __USE_GNU
#include <signal.h>
#include <poll.h>

void linux_netdev_queue_rx_wait(plane_linux_netdev_queue_t *my, 
        uint32_t timeout_us)
{
    linux_netdev_queue_t        *queue;
    struct pollfd               pollset;
    struct timespec             tmo;

    queue = container_of(my, linux_netdev_queue_t, base);

    memset(&pollset, 0, sizeof(pollset));
    pollset.fd      = queue->sock.sock_fd;
    pollset.events  = POLLIN;
    pollset.revents = 0;

    memset(&tmo, 0, sizeof(tmo));
    tmo.tv_sec  = 0;
    tmo.tv_nsec = ((long)timeout_us)*1000;

    ppoll(&pollset, 1, &tmo, NULL);
}


