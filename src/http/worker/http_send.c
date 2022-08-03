/*
 *  Rodzhang
 *
 */

#include "http_send.h"


static int _http_send_to_socket(int fd, http_response_t *rsp)
{
    char                *buff;
    int                 send_size, ret;
    int                 remain_size;

    buff        = rsp->data;
    send_size   = 0;
    remain_size = rsp->size;

    while (remain_size > 0) {

        ret = send(fd, buff, remain_size, 0);

        if (ret < 0) {
            if (errno == EINTR) {
                continue;
            }
            return -1;
        }

        send_size   += ret;
        remain_size -= ret;
        buff        += ret;
    }

    return 0;
}


int http_send_response(http_context_t *ctx)
{
    if (_http_send_to_socket(ctx->fd, &ctx->response) < 0) {
        return -1;
    }

    return 0;
}

