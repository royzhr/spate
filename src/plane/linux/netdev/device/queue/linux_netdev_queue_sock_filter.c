/*
 * Rodzhang
 *
 */


#include <spate_core.h>
#include "linux_netdev_queue_sock_filter.h"
#include "../../../plane_linux_utils.h"


int linux_netdev_queue_sock_filter(linux_netdev_queue_sock_t *sock)
{
    linux_filter_t          *filter;
    const struct sock_fprog *bpf;
    int                     ret;

    filter = __get_plane_linux_filter();

    bpf = filter->vptr->get_filter_bpf(filter);

    if (!bpf) {
        return 0;
    }

    ret = setsockopt(sock->sock_fd, SOL_SOCKET, SO_ATTACH_FILTER, bpf, sizeof(*bpf));

    LOGD("set filter opt : ret = %d", ret);

    return 0;
}


