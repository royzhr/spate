/*
 *  Rodzhang
 *
 */

#include "os_ops.h"
#include "os_mgr.h"
#include <spate_main.h>
#include <spate_event.h>


void os_default_sig_func(int sig)
{
    LOGW("\n\nSignal(%d) received, preparing to exit...\n", sig);

    g_main->quit_sig   = 1;
    g_main->force_quit = 1;

    if (g_event) {
        g_event->ops->trigger_event(EVENT_QUIT, NULL);
    }
}

static int _os_set_sig_func(void (*fn)(int sig))
{
    if (fn) {
        if (s_os_mgr->sig_process != os_default_sig_func) {
            LOGE("os sig process func already setting!");
            return -1;
        }
        s_os_mgr->sig_process = fn;

    } else {
        if (s_os_mgr->sig_process == os_default_sig_func) {
            LOGE("os sig process func not setting, but want to clear");
            return -1;
        }
        s_os_mgr->sig_process = os_default_sig_func;

    }

    return 0;
}

const os_ops_t c_os_ops = {
    .set_sig_func = _os_set_sig_func,
};


