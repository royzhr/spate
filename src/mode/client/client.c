/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_main.h>
#include <spate_module.h>
#include "client.h"
#include "client_modules.h"
#include "worker/client_worker.h"
#include "stat/client_stat.h"


/*
 * Client-Mode startup function:
 *
 */
static int _client_mode_run(void)
{
    LOGD("Client mode");

    return spate_run_with_modules(client_worker_run, c_client_modules, g_cmdline->config_file);

}

const mode_ops_t c_client_mode_ops = {
    .mode_name          = "client",
    .mode_run           = _client_mode_run,
    .mode_create_stat   = client_stat_create,
};


