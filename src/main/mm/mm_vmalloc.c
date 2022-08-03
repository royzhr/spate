/*
 * Rodzhang
 *
 */

#include "mm_vmalloc.h"


void *mm_vmalloc(uint32_t n)
{
    return malloc(n);
}

void mm_vfree(void *p, __attribute__((unused)) uint32_t n)
{
    free(p);
}
