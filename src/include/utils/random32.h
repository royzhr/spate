/*
 * Rodzhang
 */

#ifndef __RANDOM32_H__
#define __RANDOM32_H__



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


uint32_t random32(void);

void srandom32(uint32_t entropy);

int random32_init(unsigned long seed);



#endif /* __RANDOM32_H__ */
