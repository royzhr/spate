/*
 *  Rodzhang
 *
 */

#ifndef __SESSION_GRACEFUL_H__
#define __SESSION_GRACEFUL_H__


#include <spate_core.h>

typedef struct {

    int8_t              graceful_enable;
    int8_t              graceful_active;

} session_graceful_t;

int  session_graceful_init(void);
int  session_graceful_setting(void);
void session_graceful_exit(void);


#endif /* __SESSION_GRACEFUL_H__ */
