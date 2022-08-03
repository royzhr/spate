/*
 * Rodzhang
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/queue.h>
#include <signal.h>

#include <spate_core.h>
#include <spate_log.h>
#include "os_signal.h"
#include "os_mgr.h"


static void _os_signal_handler(int signum)
{
	if (signum == SIGINT || signum == SIGTERM) {

        s_os_mgr->sig_process(signum);
	}
}

int  os_signal_init(void)
{
    LOGD("os singal init");

	signal(SIGINT,  _os_signal_handler);
	signal(SIGTERM, _os_signal_handler);

    return 0;
}

void os_signal_exit(void)
{
}

