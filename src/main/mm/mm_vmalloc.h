/*
 * Rodzhang
 *
 */

#ifndef __MM_VMALLOC_H__
#define __MM_VMALLOC_H__


#include <spate_core.h>

void *mm_vmalloc(uint32_t n);
void mm_vfree(void *p, uint32_t n);



#endif /* __MM_VMALLOC_H__ */
