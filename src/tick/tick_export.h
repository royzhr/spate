/*
 * Rodzhang
 *
 */

#ifndef __TICK_EXPORT_H__
#define __TICK_EXPORT_H__


#include <spate_core.h>

typedef struct {

    uint32_t (*get_tick)(void);

    int (*add_notify)(void (*fn)(void), uint32_t later);

} tick_ops_t;


typedef struct {
    
    const tick_ops_t    *ops;

} tick_export_t;

extern tick_export_t    *g_tick;



#endif /* __TICK_EXPORT_H__ */


