/*
 *  Rodzhang
 *
 */

#ifndef __HTTP_EXPORT_H__
#define __HTTP_EXPORT_H__


#include <spate_core.h>

/*
 * 参数定义:
 * buf  : [input|ouput] 构造返回的内容buf
 * size : [input]       buf 的 size
 * len  : [ouput]       返回填写的buf的大小
 *
 * Return value:
 * 0    : ignore
 * 1    : Http 200
 * -1   : Http 404
 */

typedef int (*httpget_handler_fn)(void *user_data, const char *uri, char *buf, int size, int *len);

typedef struct {

    int  (*register_httpget_handler)(httpget_handler_fn fn, void *user_data);
    void (*unregister_httpget_handler)(httpget_handler_fn fn, void *user_data);

} http_ops_t;


typedef struct {

    const http_ops_t    *ops;

} http_export_t;


extern http_export_t    *g_http;


#endif /* __HTTP_EXPORT_H__ */

