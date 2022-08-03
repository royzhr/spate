/*
 *  Rodzhang
 *
 */

#include "session_graceful.h"
#include <spate_main.h>
#include <spate_fack_tcp.h>
#include <spate_tick.h>
#include "session_mgr.h"


static inline session_graceful_t *__get_session_graceful(void)
{
    return &s_session_mgr->graceful;
}

static void _session_graceful_timeout(void)
{
    LOGW("TCP graceful timeout and exit...");

    g_main->force_quit = 1;
}

static void _session_sig_func(int sig)
{
    if (g_main->quit_sig) {
        LOGW("\n\nSignal(%d) received again, preparing to terminate graceful and exit...\n", sig);
        g_main->force_quit = 1;
        return;
    }

    g_main->quit_sig = 1;

    __get_session_graceful()->graceful_active = 1;

    LOGW("\n\nSignal(%d) received,  preparing to graceful quit...(Send RST)\n", sig);

    g_tick->ops->add_notify(_session_graceful_timeout, g_fack_tcp->cfg.quit_graceful_timeout);
}


static inline int8_t __is_session_graceful_enable()
{
    if (g_session->cfg.proto != SPATE_TCP) {
        return 0;
    }

    if (g_fack_tcp->cfg.quit_graceful_timeout == 0) {
        return 0;
    }

    return 1;
}

int  session_graceful_init(void)
{

    return 0;
}

int  session_graceful_setting(void)
{
    session_graceful_t      *grace;

    grace = __get_session_graceful();

    grace->graceful_enable = __is_session_graceful_enable();

    if (grace->graceful_enable) {
        g_os->ops->set_sig_func(_session_sig_func);
    }

    return 0;
}

void session_graceful_exit(void)
{
    session_graceful_t      *grace;

    grace = __get_session_graceful();

    if (grace->graceful_enable) {
        g_os->ops->set_sig_func(NULL);
    }
}


