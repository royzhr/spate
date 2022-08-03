/*
 * Rodzhang
 *
 */

#ifndef __IO_MAIN_EXPORT_H__
#define __IO_MAIN_EXPORT_H__


#include <spate_core.h>

typedef struct {
    
    FILE *(*get_stdout)(void);
    FILE *(*get_stdin) (void);
    FILE *(*get_log)(void);

} io_ops_t;

typedef struct {

    const io_ops_t  *ops;

} io_export_t;

extern io_export_t  *g_io;



#endif /* __IO_MAIN_EXPORT_H__ */

