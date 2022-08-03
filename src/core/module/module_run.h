/*
 * Rodzhang
 *
 */

#ifndef __MODULE_RUN_H__
#define __MODULE_RUN_H__


#include "module_class.h"


int spate_run_with_modules(int (*run)(void *arg), const module_class_t *modules[], 
        const char *cfg_file);


#endif /* __MODULE_RUN_H__ */
