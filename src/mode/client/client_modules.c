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
#include <spate_session.h>
#include <spate_fack_tcp.h>
#include <spate_ctrl.h>
#include <spate_vxlan.h>
#include <spate_http.h>
#include <spate_event.h>

#include "client_modules.h"
#include "worker/client_worker_module.h"
#include "client_http/client_http_module.h"

/*
 * Client-Mode's Module Table
 *
 * NOTE:
 * The order of the table is very important.
 */
const module_class_t *c_client_modules[ ] = {
    &c_event_module,
    &c_plane_module,
    &c_ctrl_module,
    &c_packet_module,
    &c_tick_module,
    &c_hook_module,
    &c_host_module,
    &c_session_module,
    &c_vxlan_module,
    &c_fack_tcp_module,
    &c_client_worker_module,
    &c_stat_module,
    &c_pcap_module,
    &c_http_module,
    &c_client_http_module,
    NULL,
};


