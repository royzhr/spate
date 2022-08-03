/*
 *  Rodzhang
 *
 */

#ifndef __HTTP_HANDLER_IMP_H__
#define __HTTP_HANDLER_IMP_H__


#include "http_handler.h"

typedef struct {

    http_handler_t          base;

    /*
     * Private:
     */

    httpget_handler_fn      get_handler;
    void                    *get_handler_ud;

} http_handler_imp_t;



#endif /* __HTTP_HANDLER_IMP_H__ */
