/*
 *  Rodzhang
 *
 */

#ifndef __HTTP_CONTEXT_H__
#define __HTTP_CONTEXT_H__


#include <spate_core.h>

#define HTTP_REQ_SIZE   4096

#define HTTP_BODY_SIZE  (16*1024)

#define HTTP_RSP_SIZE   (HTTP_BODY_SIZE+1024)



typedef struct {

    char            data[HTTP_REQ_SIZE];
    int             offset;
    
    const char      *uri;

} http_request_t;

typedef struct {

    char            data[HTTP_RSP_SIZE];
    int             size;

} http_response_t;

typedef struct {

    int                     fd;

    http_request_t          request;

    http_response_t         response;

} http_context_t;


void http_context_init(http_context_t *ctx, int fd);


#endif /* __HTTP_CONTEXT_H__ */
