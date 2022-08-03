/*
 * Rodzhang
 *
 * This file records todo items in case they are forgotten.
 */

#ifndef __SPATE_TODO_H__
#define __SPATE_TODO_H__


#include <spate_core.h>


static inline uint16_t __spate_queue_nr_by_cpu(__UNUSED__ uint16_t cpu_nr)
{
    return cpu_nr;
    //return 1;
} 

static inline uint16_t __spate_queue_id_by_worker(__UNUSED__ uint16_t worker_id)
{
    return worker_id;
    //return 0;
}








#endif /* __SPATE_TODO_H__ */

