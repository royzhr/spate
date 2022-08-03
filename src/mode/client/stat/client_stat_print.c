/*
 * Rodzhang
 *
 */

#include "client_stat_print.h"
#include "client_stat_print_latency_matrix.h"
#include "client_stat_print_traffic.h"
#include "client_stat_print_session.h"


void client_stat_separator_print(void)
{
    stat_print("____________________________________________________________________"
            "____________________________\n\n");
}


void client_stat_flush_print(client_stat_t *cs)
{
    client_stat_info_t      delta;

    client_stat_info_delta(&delta, &cs->info_now, &cs->info_last);

    client_stat_print_session(&cs->info_now.session);

    client_stat_print_traffic(cs, &delta);

    client_stat_print_latency_matrix(&delta.latency, "Delta");

    stat_print("\n");

    //stat_print("\033[11A");
}


void client_stat_total_print(client_stat_t *cs)
{
    stat_print_color(SPATE_COLOR_B_GREEN, "\n\n  Statistics Before Exit: \n\n");

    client_stat_separator_print();

    client_stat_print_latency_matrix(&cs->info_now.latency, "Total");

    client_stat_separator_print();

    stat_print("Goodbye and enjoy youself.\n");
}
