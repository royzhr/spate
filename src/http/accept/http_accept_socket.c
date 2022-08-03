/*
 *  Rodzhang
 *
 */

#include "http_accept_socket.h"
#include "../http_mgr.h"
#include <sys/socket.h>
#include <netinet/in.h>


int  http_accept_socket_create(http_accept_imp_t *imp)
{
    http_cfg_t              *cfg;
    int                     fd;
    int                     ret, opt;
    struct sockaddr_in      server_addr;

    cfg = __http_cfg_block_get();

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
	server_addr.sin_addr.s_addr = htonl(cfg->listen_ip.addr);
	server_addr.sin_port        = htons(cfg->listen_port.port);

    opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    ret = bind(fd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr));
    if (ret < 0) {
        LOGE("http module bind error!");
        close(fd);
        return -1;
    }

    ret = listen(fd, 8);
    if (ret < 0) {
        LOGE("http module listen error!");
        close(fd);
        return -1;
    }


    imp->listen_fd = fd;

    return 0;
}

void http_accept_socket_destroy(http_accept_imp_t *imp)
{
    close(imp->listen_fd);
    imp->listen_fd = -1;
}


