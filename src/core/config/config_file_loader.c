/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include "config_file_loader.h"
#include "config_parse.h"
#include <spate_utils.h>




static int _config_process_line(char *str, const config_file_loader_ops_t *loader, 
        void *ud, int line)
{
    char                *p;
    char                *key, *val;
    int                 ret;

    if (*str == '#')
        return 0;

    p = strchr(str, '=');
    if (p == NULL)
        return 0;
    
    *p = 0;

    key = str;
    val = p + 1;

    key = __config_string_strip_space(key);
    val = __config_string_strip_space(val);

    __string_to_lower(key);
    // val maybe used as path, cant covert to lower
    //__string_to_lower(val);

    LOGD("parse: %s : %s", key, val);
    ret = loader->cfg_parse_line(key, val, ud);

    if (ret == 0) {
        LOGW("confilg line(%d) cant process : %s = %s", line, key, val);
    }

    return ret;
}

int  config_file_load(const char *cfg_file, const config_file_loader_ops_t *loader, void *ud)
{
    FILE                *f;
    int                 ret, line;
    char                buf[CFG_MAX_PER_LINE+1];

    ret  = 0;
    line = 0;

    f = fopen(cfg_file, "r");

    if (!f) {
        LOGE("read config file :%s cant open!", cfg_file);
        return -1;
    }

    loader->cfg_begin(ud);

    for (;;) {
        if (fgets(buf, CFG_MAX_PER_LINE, f) == NULL) {
            break;
        }

        if (feof(f)) 
            break;

        buf[CFG_MAX_PER_LINE] = 0;

        ret = _config_process_line(buf, loader, ud, ++line);
        if (ret < 0) {
            LOGE("config file:%s parse error on line:%d", cfg_file, line);
            break;
        }
    }

    if (!ret) {
        ret = loader->cfg_finish(ud);
    }

    fclose(f);

    return ret;
}

