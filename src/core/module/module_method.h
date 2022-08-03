/*
 * Rodzhang
 *
 */

#ifndef __MODULE_METHOD_H__
#define __MODULE_METHOD_H__



#include "module_class.h"


int  spate_modules_init(const module_class_t *modules_table[]);
int  spate_modules_setting(const module_class_t *modules_table[]);
void spate_modules_exit(const module_class_t *modules_table[]);

void spate_modules_cfg_begin(const module_class_t *modules_table[]);
int  spate_modules_cfg_finish(const module_class_t *modules_table[]);
int  spate_modules_cfg_parse_line( const char *key, const char *val, 
        const module_class_t *modules_table[]);


#endif /* __MODULE_METHOD_H__ */

