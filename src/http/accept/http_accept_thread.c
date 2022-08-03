/*
 *  Rodzhang
 *
 */

#include "http_accept_thread.h"
#include "http_accept_instance.h"


int  http_accept_thread_create(http_accept_imp_t *imp)
{
    int                     ret;

    ret = pthread_create(&imp->accept_thread, NULL, http_accept_instance_run, imp);
    if (ret < 0) {
        return -1;
    }

    return 0;
}

void http_accept_thread_destroy(http_accept_imp_t *imp)
{
    pthread_join(imp->accept_thread, NULL);
}


