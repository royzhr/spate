/*
 * Rodzhang
 *
 */

#ifndef __MODE_CLASS_H__
#define __MODE_CLASS_H__

#include <spate_core.h>
#include <spate_stat.h>

/*
 * run-mode's arg
 */
typedef struct {
    
    const char      *mode;

    const char      *config_file;

} mode_args_t;


typedef struct {
    
    const char  *mode_name;

    int (*mode_run)(void);

    stat_t *(*mode_create_stat)(void);

} mode_ops_t;




#endif /* __MODE_CLASS_H__ */

