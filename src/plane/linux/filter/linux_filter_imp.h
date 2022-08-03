/*
 * Rodzhang
 *
 */

#ifndef __LINUX_FILTER_IMP_H__
#define __LINUX_FILTER_IMP_H__


#include "linux_filter_export.h"
#include <linux/filter.h>

typedef struct {

    linux_filter_t      base;

    int                 has_filter;

    struct sock_fprog   bpf_code;

} linux_filter_imp_t;



#endif /* __LINUX_FILTER_IMP_H__ */
