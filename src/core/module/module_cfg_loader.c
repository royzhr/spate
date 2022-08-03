/*
 * Rodzhang
 *
 */

#include "module_cfg_loader.h"
#include "module_method.h"
#include <spate_main.h>


static void _module_config_begin(void *user_data)
{
    const module_class_t    **modules;

    modules = (const module_class_t **)user_data;

    spate_modules_cfg_begin(modules);
}

static int _module_config_finish(void *user_data)
{
    const module_class_t    **modules;

    modules = (const module_class_t **)user_data;

    return spate_modules_cfg_finish(modules);
}

static int _module_config_parse_line(const char *key, const char *val, void *user_data)
{
    int                     ret;
    const module_class_t    **modules;

    modules = (const module_class_t **)user_data;

    ret = spate_modules_cfg_parse_line(key, val, modules);

    if (ret) {
        return ret;
    }

    if (!strcmp(key, "mode")) {

        if (strcmp(val, g_rt_mode->current_mode_ops->mode_name)) {
            LOGE("Wrong mode");
            return -1;
        }

    }

    return 0;
}

const config_file_loader_ops_t c_module_config_loader_ops = {
    .cfg_begin      = _module_config_begin,
    .cfg_finish     = _module_config_finish,
    .cfg_parse_line = _module_config_parse_line,
};


