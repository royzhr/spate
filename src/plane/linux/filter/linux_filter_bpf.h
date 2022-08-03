/*
 * Rodzhang
 *
 */

#ifndef __LINUX_FILTER_BPF_H__
#define __LINUX_FILTER_BPF_H__


#include "linux_filter_imp.h"

int  linux_filter_bpf_constructor(struct sock_fprog *bpf_code, const char *filter_string);
void linux_filter_bpf_destructor(struct sock_fprog *bpf_code);


#endif /* __LINUX_FILTER_BUILD_BPF_H__ */
