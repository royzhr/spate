/*
 *  Rodzhang
 *
 */

#include "http_build_response.h"
#include <spate_main.h>
#include "../http_mgr.h"


static void _http_build_404(http_response_t *rsp)
{
    char                    *data;
    int                     size;

    data = rsp->data;
    size = 0;

    size += sprintf(data+size, "HTTP/1.0 404 File not found\r\n");
    size += sprintf(data+size, "Server: spate-%s\r\n", spate_version_get());
    size += sprintf(data+size, "Connection: close\r\n");
    size += sprintf(data+size, "Content-Type: text/html;charset=utf-8\r\n");
    size += sprintf(data+size, "Content-Length: 0\r\n\r\n");

    rsp->size = size;
}

static void _http_build_200(http_response_t *rsp, char *body, int body_len)
{
    char                    *data;
    int                     size;

    data = rsp->data;
    size = 0;

    size += sprintf(data+size, "HTTP/1.0 200 OK\r\n");
    size += sprintf(data+size, "Server: spate-%s\r\n", spate_version_get());
    size += sprintf(data+size, "Connection: close\r\n");
    size += sprintf(data+size, "Content-Type: text/html;charset=utf-8\r\n");
    size += sprintf(data+size, "Content-Length: %d\r\n\r\n", body_len);

    memcpy(data+size, body, body_len);
    size += body_len;

    rsp->size = size;
}

static void _http_build_error(http_response_t *rsp, char *body, int body_len)
{
    char                    *data;
    int                     size;

    data = rsp->data;
    size = 0;

    size += sprintf(data+size, "HTTP/1.0 404 Error\r\n");
    size += sprintf(data+size, "Server: spate-%s\r\n", spate_version_get());
    size += sprintf(data+size, "Connection: close\r\n");
    size += sprintf(data+size, "Content-Type: text/html;charset=utf-8\r\n");
    size += sprintf(data+size, "Content-Length: %d\r\n\r\n", body_len);

    memcpy(data+size, body, body_len);
    size += body_len;

    rsp->size = size;
}


int http_build_response(http_context_t *ctx)
{
    http_handler_t          *handler;
    int                     ret;
    char                    body_data[HTTP_BODY_SIZE];
    int                     body_len;

    handler = s_http_mgr->http_handler;

    body_len = 0;
    ret = handler->vptr->call_get_handler(handler, ctx->request.uri, 
            body_data, HTTP_BODY_SIZE, &body_len);

    if (ret == 1) {
        // 200OK
        _http_build_200(&ctx->response, body_data, body_len);

    } else if (ret == -1) {
        // 404
        _http_build_error(&ctx->response, body_data, body_len);

    } else {
        _http_build_404(&ctx->response);

    }

    return 0;
}


