/*
 * Rodzhang
 *
 */

#ifndef __RT_MODE_EXPORT_H__
#define __RT_MODE_EXPORT_H__


#include <spate_core.h>
#include <spate_mode.h>


typedef struct {


    const mode_ops_t    *current_mode_ops;
    

} rt_mode_export_t;

extern rt_mode_export_t *g_rt_mode;



#endif /* __RT_MODE_EXPORT_H__ */
