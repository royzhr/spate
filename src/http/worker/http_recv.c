/*
 *  Rodzhang
 *
 */

#include "http_recv.h"

/*
 * Return value:
 * 0  : Continue
 * 1  : Finish and ok
 * -1 : Error
 */
static int _http_request_check(http_request_t *req)
{
    char                *data;
    char                *last;

    if (req->offset == HTTP_REQ_SIZE) {
        return -1;
    } else if (req->offset < 4) {
        return 0;
    }

    //LOGW("http req offset: %d", req->offset);

    data = req->data;
    
    if (data[0]!='G' || data[1]!='E' || data[2]!='T' || data[3]!=' ') {
        return -1;
    }

    last = req->data + req->offset - 4;

    //LOGW("last: %x %x %x %x", last[0], last[1], last[2], last[3]);

    if (last[0]=='\r' && last[1]=='\n' && last[2]=='\r' && last[3]=='\n') {
        return 1;
    }

    return 0;
}

static int _http_recv_from_socket(int fd, http_request_t *req)
{
    char                *buff;
    int                 buf_size;
    int                 ret, recv_size;

    buff      = req->data;
    recv_size = 0;
    buf_size  = HTTP_REQ_SIZE;

    for ( ; ; ) {
        ret = recv(fd, buff, buf_size, 0);

        if (ret < 0) {
            if (errno == EINTR) {
                continue;
            }
            LOGE("http recv errno: %d", errno);
            return -1;
        } else if (ret == 0) {
            return -1;
        }

        recv_size += ret;
        buff      += ret;
        buf_size  -= ret;

        req->offset = recv_size;

        ret = _http_request_check(req);
        if (ret < 0) {
            return -1;
        } else if (ret > 0) {
            break;
        }
    }

    return 0;
}

static int _http_request_parse_uri(http_request_t *req)
{
    char                *p;

    req->uri = req->data + 4;
    
    for (p=(char*)req->uri; p<req->data+req->offset; ++p) {
        if (*p == ' ') {
            *p = '\0';
            return 0;
        }
    }

    return -1;
}


int http_recv_request(http_context_t *ctx)
{
    if (_http_recv_from_socket(ctx->fd, &ctx->request) < 0) {
        return -1;
    }

    if (_http_request_parse_uri(&ctx->request) < 0) {
        return -1;
    }

    //LOGW("uri: %s", ctx->request.uri);

    return 0;
}

