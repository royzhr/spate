/*
 * Rodzhang
 *
 * module of main (Distinguish from mode-module)
 *
 * main-module does not use config file, it needs to parse argc&argv
 */

#ifndef __MAIN_MODULE_H__
#define __MAIN_MODULE_H__


#include <spate_core.h>

typedef struct {

    const char              *name;

    int  (*init)(int argc, char **argv);
    void (*exit)(void);

    /*
     * Can Be NULL
     */
    void (*run)(void);

} main_module_t;


int  main_module_init(int argc, char **argv);
void main_module_run(void);
void main_module_exit(void);


#endif /* __MAIN_MODULE_H__ */

