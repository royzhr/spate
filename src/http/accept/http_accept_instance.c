/*
 *  Rodzhang
 *
 */

#include "http_accept_instance.h"
#include "http_accept_imp.h"
#include <spate_main.h>
#include <spate_ctrl.h>
#include "../worker/http_worker.h"



void *http_accept_instance_run(void *arg)
{
    http_accept_imp_t       *imp;
    int                     conn_fd;

    imp = (http_accept_imp_t *)arg;

    for ( ; ; ) {
        conn_fd = accept(imp->listen_fd, NULL, NULL);

        if (conn_fd >= 0) {
            // new client connect 
            //LOGW("http accept connection fd: %d", conn_fd);

            http_worker_run(conn_fd);
        }

    }

    return NULL;
}
