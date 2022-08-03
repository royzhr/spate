/*
 * Rodzhang
 *
 */

#ifndef __LINUX_FILTER_METHOD_H__
#define __LINUX_FILTER_METHOD_H__


#include "linux_filter_imp.h"

int  linux_filter_constructor(linux_filter_imp_t *imp);
void linux_filter_destructor(linux_filter_imp_t *imp);


#endif /* __LINUX_FILTER_METHOD_H__ */
