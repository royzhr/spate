/*
 * Rodzhang
 *
 */

#include <spate_tick.h>
#include <spate_packet.h>
#include <spate_hook.h>
#include <spate_host.h>
#include <spate_stat.h>
#include <spate_pcap.h>
#include <spate_plane.h>
#include <spate_server_listen.h>
#include <spate_ctrl.h>
#include <spate_http.h>
#include <spate_event.h>

#include "server_modules.h"

#include "worker/server_worker_module.h"


/*
 * Server-Mode's Module Table
 *
 * NOTE:
 * The order of the table is very important.
 */
const module_class_t *c_server_modules[ ] = {
    &c_event_module,
    &c_plane_module,
    &c_ctrl_module,
    &c_tick_module,
    &c_hook_module,
    &c_host_module,
    &c_server_listen_module,
    &c_server_worker_module,
    &c_stat_module,
    &c_pcap_module,
    &c_http_module,
    NULL,
};


