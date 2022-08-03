/*
 *  Rodzhang
 *
 */

#include <spate_core.h>
#include <pthread.h>
#include "http_worker.h"
#include "http_worker_instance.h"



void http_worker_run(int conn_fd)
{
    pthread_t           thread;
    int                 ret;

    ret = pthread_create(&thread, NULL, http_worker_instance_run, (void*)((intptr_t)conn_fd));

    if (ret < 0) {
        LOGE("http worker run thread error");
        close(conn_fd);
    }
}
