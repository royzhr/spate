/*
 *  Rodzhang
 *
 */

#ifndef __PLANE_LINUX_EXTEND_MODULE_H__
#define __PLANE_LINUX_EXTEND_MODULE_H__


#include <spate_module.h>

#define __spate_linux_extend_module__           \
    __attribute__((unused, section("spate_linux_extend_module_register")))


int  plane_linux_extend_module_init(void);
int  plane_linux_extend_module_setting(void);
void plane_linux_extend_module_exit(void);


void plane_linux_extend_module_cfg_begin();
int  plane_linux_extend_module_cfg_finish();
int  plane_linux_extend_module_cfg_parse_line(const char *key, const char *val);


#endif /* __PLANE_LINUX_EXTEND_MODULE_H__ */

