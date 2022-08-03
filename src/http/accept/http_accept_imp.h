/*
 *  Rodzhang
 *
 */

#ifndef __HTTP_ACCEPT_IMP_H__
#define __HTTP_ACCEPT_IMP_H__


#include "http_accept.h"
#include <pthread.h>


typedef struct {

    http_accept_t       base;

    pthread_t           accept_thread;

    int                 listen_fd;

} http_accept_imp_t;



#endif /* __HTTP_ACCEPT_rMP_H__ */
