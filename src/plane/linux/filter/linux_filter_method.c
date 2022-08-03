/*
 * Rodzhang
 *
 */

#include <spate_main.h>
#include "linux_filter_method.h"
#include "linux_filter_vtbl.h"
#include "linux_filter_bpf.h"
#include "linux_filter_mode.h"


#define LINUX_FILTER_STRING_LEN     512


static int _linux_filter_build_string(linux_filter_imp_t *imp, char *str, uint16_t len)
{
    int                 ret;

    ret = -1;

    switch (g_main->ops->get_mode()) {
        case SPATE_MODE_CLIENT:
            ret = build_filter_string_mode_client(str, len);
            break;

        case SPATE_MODE_SERVER:
            ret = build_filter_string_mode_server(str, len);
            break;

        default:
            return -1;
    }

    return ret;
}


static inline int __linux_filter_build(linux_filter_imp_t *imp)
{
    char                str[LINUX_FILTER_STRING_LEN];

    if (_linux_filter_build_string(imp, str, LINUX_FILTER_STRING_LEN) < 0) {
        return -1;
    }

    LOGW("linux filter string: %s", str);

    if (linux_filter_bpf_constructor(&imp->bpf_code, str) < 0) {
        return -1;
    }

    return 0;
}

int  linux_filter_constructor(linux_filter_imp_t *imp)
{
    memset(imp, 0, sizeof(*imp));

    imp->base.vptr = &c_linux_filter_vtbl;

    if (__linux_filter_build(imp) < 0) {
        imp->has_filter = 0;
    } else {
        imp->has_filter = 1;
    }

    LOGW("linux_filter build : %d", imp->has_filter);

    return 0;
}

void linux_filter_destructor(linux_filter_imp_t *imp)
{
    if (imp->has_filter) {
        linux_filter_bpf_destructor(&imp->bpf_code);
        imp->has_filter = 0;
    }

    imp->base.vptr = NULL;
}

