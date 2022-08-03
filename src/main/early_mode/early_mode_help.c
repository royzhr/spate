/*
 * Rodzhang
 *
 */

#include "early_mode_help.h"
#include "early_mode_version.h"
#include <spate_print.h>


void early_mode_help(void)
{
    __spate_print("The cmd-line supported list:\n");
    __spate_print("-c <config_file>    : specify the config file\n");
    __spate_print("-m <worker_mode>    : client or server\n");
    __spate_print("-p <plane of Tx&Rx> : linux or dpdk or ebpf , default is linux\n");
    __spate_print("-v                  : version \n");
    __spate_print("-s                  : show support plane\n");
    __spate_print("-h                  : help\n");
    __spate_print("-L                  : show LOG of spate\n");

    __spate_print("\n");

    __spate_print("For example: \n");
    __spate_print("Startup cilent-mode by default(linux raw socket) plane. Please use: \n");
    __spate_print_color(SPATE_COLOR_B_NORMAL, "spate -m client -c my_client.cfg\n");
    __spate_print("Startup server-mode by DPDK plane. Please use: \n");
    __spate_print_color(SPATE_COLOR_B_NORMAL, "spate -m server -c my_server.cfg -p dpdk ");
    __spate_print_color(SPATE_COLOR_B_GREEN, " -- -l 0-0\n");
    __spate_print("Note: The green color of cmd-line is used by DPDK. For details, "
            "please refer to the DPDK document.\n");

    __spate_print("\n\n");
    __spate_print("Purpose: Make network performance testing easier.\n");
    __spate_print("\n\n");
}

