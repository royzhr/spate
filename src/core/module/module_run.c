/*
 * Rodzhang
 *
 */

#include "module_run.h"
#include <spate_plane.h>
#include "module_cfg_loader.h"
#include "module_method.h"


static inline int __spate_mode_load_config(const char *cfg_file, const module_class_t *modules[])
{
    return config_file_load(cfg_file, &c_module_config_loader_ops, modules);
}

static int _spate_executor_run(int (*fn)(void *arg))
{
    return g_plane->worker_frame->vptr->executor_worker(g_plane->worker_frame, fn);
}

static void _spate_executor_wait(void)
{
    g_plane->worker_frame->vptr->executor_wait(g_plane->worker_frame);
}



int spate_run_with_modules(int (*run)(void *arg), const module_class_t *modules[], 
        const char *cfg_file)
{
    /* Module init */
    if (spate_modules_init(modules) < 0) {
        return -1;
    }

    /* Load Config (Module load config) */
    if (__spate_mode_load_config(cfg_file, modules) < 0) {
        LOGE("Config File load error: %s", cfg_file);
        return -1;
    }

    /* Module setting */
    if (spate_modules_setting(modules) < 0) {
        return -1;
    }

    if (_spate_executor_run(run) < 0) {
        return -1;
    }

    _spate_executor_wait();

    spate_modules_exit(modules);

    return 0;
}


