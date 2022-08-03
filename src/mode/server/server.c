/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_main.h>
#include <spate_module.h>
#include "server.h"
#include "server_modules.h"
#include "worker/server_worker.h"
#include "stat/server_stat.h"


/*
 * Server-Mode startup function:
 *
 */
static int _server_mode_run(void)
{
    LOGD("Server mode");

    return spate_run_with_modules(server_worker_run, c_server_modules, g_cmdline->config_file);

}


const mode_ops_t c_server_mode_ops = {
    .mode_name          = "server",
    .mode_run           = _server_mode_run,
    .mode_create_stat   = server_stat_create,
};

