/*
 * Rodzhang
 *
 */

#include "linux_netdev_info.h"
#include "linux_netdev_vtbl.h"


int linux_netdev_info_get(plane_linux_netdev_t *netdev, linux_netdev_cfg_t *cfg)
{
    int                 sock;
    struct ifreq        ifr;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        return -1;
    }

    memset(&ifr, 0, sizeof(ifr));
    
    if (strlen(cfg->name) >= sizeof(ifr.ifr_name)) {
        return -1;
    }

	strcpy(ifr.ifr_name, cfg->name);

	if (ioctl(sock, SIOCGIFHWADDR, &ifr) < 0) {
        goto sock_error;
    }

    memcpy(netdev->base.info.mac_addr, ifr.ifr_hwaddr.sa_data, ETH_ALEN);

	if (ioctl(sock, SIOCGIFINDEX, &ifr) < 0) {
        goto sock_error;
    }

    netdev->if_index = ifr.ifr_ifindex;

    netdev->queue_nr = __plane_get_worker_nr();

    netdev->base.vptr = &c_linux_netdev_base_vtbl;

    close(sock);
    return 0;

sock_error:
    close(sock);
    return -1;
}

void linux_netdev_info_put(plane_linux_netdev_t *netdev)
{
    netdev->base.vptr = NULL;
}
