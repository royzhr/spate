/*
 *  Rodzhang
 *
 */

#ifndef __HTTP_ACCEPT_THREAD_H__
#define __HTTP_ACCEPT_THREAD_H__


#include "http_accept_imp.h"

int  http_accept_thread_create(http_accept_imp_t *imp);
void http_accept_thread_destroy(http_accept_imp_t *imp);



#endif /* __HTTP_ACCEPT_THREAD_H__ */
