/*
 *  Rodzhang
 *
 */

#include "http_parse_uri.h"


int http_parse_uri_params(const char *uri, const char *key, char *val, int size)
{
    const char              *p;
    const char              *k, *v, *e;
    int                     len;

    // Find '?'

    p = strchr(uri, '?');

    if (!p) {
        return -1;
    }

    k = strstr(p, key);

    if (!k) {
        return -1;
    }

    k += strlen(key);

    if (*k != '=') {
        return -1;
    }

    v = k + 1;

    // Find tail
    e = v;
    for ( ; ; ) {
        if (*e=='&' || *e=='\r' || *e=='\n' || *e==' ' || *e==0) {
            break;
        }
        e++;
    }

    len = e - v;

    if (len==0 || len>=size) {

        return -1;
    }
    
    memcpy(val, v, len);
    val[len] = 0;


    return 0;
}


