/*
 *  Rodzhang
 *
 */

#ifndef __OS_EXPORT_H__
#define __OS_EXPORT_H__


#include <spate_core.h>


typedef struct {

    int (*set_sig_func)(void (*fn)(int sig));

} os_ops_t;


typedef struct {

    const os_ops_t      *ops;

} os_export_t;

extern os_export_t *g_os;


#endif /* __OS_EXPORT_H__ */
