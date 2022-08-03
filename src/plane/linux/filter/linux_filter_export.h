/*
 * Rodzhang
 *
 */

#ifndef __LINUX_FILTER_EXPORT_H__
#define __LINUX_FILTER_EXPORT_H__


#include <stdint.h>
#include <linux/filter.h>


struct linux_filter_s;


typedef struct {

    const struct sock_fprog * (*get_filter_bpf)(struct linux_filter_s *my);

    void (*destroy)(struct linux_filter_s *my);

} linux_filter_vtbl_t;


typedef struct linux_filter_s {

    const linux_filter_vtbl_t     *vptr;

} linux_filter_t;



#endif /* __LINUX_FILTER_EXPORT_H__ */

