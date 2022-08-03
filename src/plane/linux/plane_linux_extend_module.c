/*
 *  Rodzhang
 *
 */

#include "plane_linux_extend_module.h"
#include "plane_linux_extend_lds.h"



int  plane_linux_extend_module_init(void)
{
    const module_class_t    *mod;

    for (mod=__spate_linux_extend_module_start; mod<__spate_linux_extend_module_end; mod++) {
        if (mod->module_init() < 0) {
            LOGE("module %s init error!", mod->module_name);
            return -1;
        }
    }

    return 0;
}

int  plane_linux_extend_module_setting(void)
{
    const module_class_t    *mod;

    for (mod=__spate_linux_extend_module_start; mod<__spate_linux_extend_module_end; mod++) {
        if (mod->module_setting() < 0) {
            LOGE("module %s setting error!", mod->module_name);
            return -1;
        }
    }
    return 0;
}

void plane_linux_extend_module_exit(void)
{
    const module_class_t    *mod;

    for (mod=__spate_linux_extend_module_start; mod<__spate_linux_extend_module_end; mod++) {
        mod->module_exit();
    }
}



void plane_linux_extend_module_cfg_begin()
{
    const module_class_t    *mod;
    const module_cfg_ops_t  *cfg;

    for (mod=__spate_linux_extend_module_start; mod<__spate_linux_extend_module_end; mod++) {
        cfg = mod->cfg_ops;

        if (cfg) {
            cfg->begin();
        }
    }
}

int plane_linux_extend_module_cfg_finish()
{
    const module_class_t    *mod;
    const module_cfg_ops_t  *cfg;

    for (mod=__spate_linux_extend_module_start; mod<__spate_linux_extend_module_end; mod++) {
        cfg = mod->cfg_ops;

        if (cfg) {
            if (cfg->finish() < 0) {
                return -1;
            }
        }
    }

    return 0;
}

int plane_linux_extend_module_cfg_parse_line(const char *key, const char *val)
{
    const module_class_t    *mod;
    const module_cfg_ops_t  *cfg;
    int                     ret;

    for (mod=__spate_linux_extend_module_start; mod<__spate_linux_extend_module_end; mod++) {
        cfg = mod->cfg_ops;

        if (cfg) {
            ret = cfg->parse_line(key, val);
            
            if (ret) {
                return ret;
            }
        }
    }
    return 0;
}
