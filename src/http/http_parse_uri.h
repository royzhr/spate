/*
 *  Rodzhang
 *
 */

#ifndef __HTTP_PARSE_URI_H__
#define __HTTP_PARSE_URI_H__


#include <spate_core.h>

#define SPATE_URI_PARAMS_SIZE   64

/*
 * Return Value:
 * 0    : get params ok
 * -1   : parse error
 */
int http_parse_uri_params(const char *uri, const char *key, char *val, int size);



#endif /* __HTTP_PARSE_URI_H__ */
