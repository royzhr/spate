/*
 * Rodzhang
 */

#ifndef __MEM_BARRIER_H__
#define __MEM_BARRIER_H__


#include <stdint.h>
#include <sys/types.h>



#define MB() __asm__ __volatile__("": : :"memory")



#define SMP_MB() asm volatile("lock; addl $0,-4(%%rsp)" ::: "memory", "cc")



#endif /* __MEM_BARRIER_H__ */



