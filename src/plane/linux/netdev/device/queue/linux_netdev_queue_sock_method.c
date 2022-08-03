/*
 * Rodzhang
 *
 */

#include "linux_netdev_queue_sock_method.h"
#include "linux_netdev_queue_sock_filter.h"
#include <spate_utils.h>


static int _linux_netdev_queue_socket_create(int if_index)
{
    int                     fd;
	struct sockaddr_ll      addr;

    fd = socket(PF_PACKET, SOCK_RAW, ETH_P_ALL);
    if (fd < 0) {
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
	addr.sll_family   = PF_PACKET;
	addr.sll_protocol = htons(ETH_P_ALL);
	addr.sll_ifindex  = if_index;

    if (bind(fd, (void*)&addr, sizeof(addr)) < 0) {
        goto sock_error;
    }

    /*
     * Note: Must use blocking fd.
     */
//    if (__set_noblocking(fd) < 0) {
//        goto sock_error;
//    }

    return fd;

sock_error:
    close(fd);
    return -1;
}

static int _linux_netdev_queue_sock_fanout(linux_netdev_queue_sock_t *sock)
{
    int                     fanout_arg;
    int                     fanout_id;
    int                     fanout_type;

    fanout_id   = getpid() & 0xFFFF;
    fanout_type = PACKET_FANOUT_HASH;

    fanout_arg = (fanout_id | (fanout_type << 16));
    if (setsockopt(sock->sock_fd, SOL_PACKET, PACKET_FANOUT, &fanout_arg, sizeof(fanout_arg)) < 0) {
        return -1;
    }

    return 0;
}

static int _linux_netdev_queue_sock_ring(linux_netdev_queue_sock_t *sock)
{
    int                     ver;
    struct tpacket_req      req;

    ver = TPACKET_V1;

    if (setsockopt(sock->sock_fd, SOL_PACKET, PACKET_VERSION, &ver, sizeof(ver)) < 0) {
        return -1;
    }

    memset(&req, 0, sizeof(req));
	req.tp_block_size       = sock->frame_size * sock->rx_nr;
	req.tp_frame_size       = sock->frame_size;
	req.tp_block_nr         = 1;
	req.tp_frame_nr         = sock->rx_nr;
    if (setsockopt(sock->sock_fd, SOL_PACKET, PACKET_RX_RING, &req, sizeof(req)) < 0) {
        return -1;
    }

    memset(&req, 0, sizeof(req));
	req.tp_block_size       = sock->frame_size * sock->tx_nr;
	req.tp_frame_size       = sock->frame_size;
	req.tp_block_nr         = 1;
	req.tp_frame_nr         = sock->tx_nr;
    if (setsockopt(sock->sock_fd, SOL_PACKET, PACKET_TX_RING, &req, sizeof(req)) < 0) {
        return -1;
    }

    return 0;
}

static int _linux_netdev_queue_sock_bypass_qdisc(linux_netdev_queue_sock_t *sock, 
        linux_netdev_cfg_t *cfg)
{
    int                 one;

    one = cfg->is_bypass_qdisc;

    if (setsockopt(sock->sock_fd, SOL_PACKET, PACKET_QDISC_BYPASS, &one, sizeof(one)) < 0) {
        return -1;
    }

    return 0;
}

static int _linux_netdev_queue_sock_opt(linux_netdev_queue_sock_t *sock, 
        linux_netdev_cfg_t *cfg)
{
    if (_linux_netdev_queue_sock_ring(sock) < 0) {
        return -1;
    }

    if (_linux_netdev_queue_sock_fanout(sock) < 0) {
        return -1;
    }

    if (linux_netdev_queue_sock_filter(sock) < 0) {
        return -1;
    }

    if (_linux_netdev_queue_sock_bypass_qdisc(sock, cfg) < 0) {
        return -1;
    }

    return 0;
}

static int _linux_netdev_queue_sock_map(linux_netdev_queue_sock_t *sock)
{
    sock->map = mmap(0, sock->map_size, PROT_READ|PROT_WRITE, 
            MAP_SHARED, sock->sock_fd, 0);

    if (sock->map == MAP_FAILED) {
        LOGE("linux netdev sock mmap error, size=%u, errno=%d", sock->map_size, errno);
        return -1;
    }

    sock->map_rx = sock->map;
    sock->map_tx = sock->map + sock->rx_size;

    return 0;
}

static void _linux_netdev_queue_sock_unmap(linux_netdev_queue_sock_t *sock)
{
    munmap(sock->map, sock->map_size);

    sock->map    = NULL;
    sock->map_rx = NULL;
    sock->map_tx = NULL;
}


static void _linux_netdev_queue_sock_fill(linux_netdev_queue_sock_t *sock, 
        linux_netdev_cfg_t *cfg)
{
    sock->rx_nr    = cfg->rx_desc;
    sock->tx_nr    = cfg->tx_desc;

    sock->rx_size  = sock->rx_nr * sizeof(linux_netdev_queue_frame_t);
    sock->tx_size  = sock->tx_nr * sizeof(linux_netdev_queue_frame_t);

    sock->map_size = sock->rx_size + sock->tx_size;

    sock->frame_size = sizeof(linux_netdev_queue_frame_t);

    LOGD("linux netdev queue sock frame_size:%u", sock->frame_size);

    ASSERT(is_power_of_2(sock->frame_size));
}

int  linux_netdev_queue_sock_constructor(linux_netdev_queue_sock_t *sock, 
       plane_linux_netdev_t *netdev, linux_netdev_cfg_t *cfg)
{
    sock->sock_fd = _linux_netdev_queue_socket_create(netdev->if_index);
    if (sock->sock_fd < 0) {
        return -1;
    }

    _linux_netdev_queue_sock_fill(sock, cfg);

    if (_linux_netdev_queue_sock_opt(sock, cfg) < 0) {
        LOGE("linux netdev queue sockopt error");
        goto sock_error;
    }

    if (_linux_netdev_queue_sock_map(sock) < 0) {
        goto sock_error;
    }

    return 0;

sock_error:
    close(sock->sock_fd);
    return -1;
}

void linux_netdev_queue_sock_destructor(linux_netdev_queue_sock_t *sock)
{
    _linux_netdev_queue_sock_unmap(sock);

    close(sock->sock_fd);
}


