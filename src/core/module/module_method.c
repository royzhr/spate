/*
 * Rodzhang
 *
 */

#include "module_method.h"


/*
 * How many module in modules_table:
 */
static inline int __spate_modules_count(const module_class_t *modules_table[])
{
    const module_class_t    *module;
    int                     i;

    for (i=0; ; ++i) {
        module = modules_table[i];

        if (!module) {
            break;
        }
    }

    return i;
}

int  spate_modules_setting(const module_class_t *modules_table[])
{
    const module_class_t    *module;
    int                     i;

    for (i=0, module=modules_table[i]; module!=NULL; ++i,module=modules_table[i]) {
        if (module->module_setting) {
            if (module->module_setting() < 0) {
                return -1;
            }
        }
    }

    return 0;
}

int  spate_modules_init(const module_class_t *modules_table[])
{
    const module_class_t    *module;
    int                     i;

    for (i=0, module=modules_table[i]; module!=NULL; ++i,module=modules_table[i]) {
        if (module->module_init() < 0) {
            LOGE("module %s init error!", module->module_name);
            return -1;
        }
    }

    return 0;
}


void spate_modules_exit(const module_class_t *modules_table[])
{
    const module_class_t    *module;
    int                     i;

    i = __spate_modules_count(modules_table) - 1;

    for (module=modules_table[i]; i>=0; --i,module=modules_table[i]) {
        module->module_exit();
    }
}


void spate_modules_cfg_begin(const module_class_t *modules_table[])
{
    const module_class_t    *module;
    const module_cfg_ops_t  *cfg;
    int                     i;

    for (i=0; ; ++i) {
    
        module = modules_table[i];
        if (!module) {
            break;
        }

        cfg = module->cfg_ops;
        if (!cfg) {
            continue;
        }

        cfg->begin();
    }
}

int spate_modules_cfg_finish(const module_class_t *modules_table[])
{
    const module_class_t    *module;
    const module_cfg_ops_t  *cfg;
    int                     i;

    for (i=0; ; ++i) {
    
        module = modules_table[i];
        if (!module) {
            break;
        }

        cfg = module->cfg_ops;
        if (!cfg) {
            continue;
        }

        if (cfg->finish() < 0) {
            return -1;
        }
    }

    return 0;
}

int  spate_modules_cfg_parse_line(const char *key, const char *val, 
        const module_class_t *modules_table[])
{
    const module_class_t    *module;
    const module_cfg_ops_t  *cfg;
    int                     i, ret;

    for (i=0; ; ++i) {
    
        module = modules_table[i];
        if (!module) {
            break;
        }

        cfg = module->cfg_ops;
        if (!cfg) {
            continue;
        }

        ret = cfg->parse_line(key, val);

        if (ret) {
            return ret;
        }
    }

    return 0;
}
