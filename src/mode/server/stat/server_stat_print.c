/*
 * Rodzhang
 *
 */

#include "server_stat_print.h"
#include "../worker/server_worker.h"


static void _server_stat_print_worker(const server_stat_info_t *ss, uint16_t worker_id)
{
    char        worker_rx    [CSP_TRAFFIC_LEN];
    char        worker_tx    [CSP_TRAFFIC_LEN];
    char        worker_busy  [CSP_TRAFFIC_LEN];

    __stat_traffic_get_string(worker_rx, CSP_TRAFFIC_LEN, SPATE_COLOR_NORMAL, 
            ss->traffic.rx_pkts);
    __stat_traffic_get_string(worker_tx, CSP_TRAFFIC_LEN, SPATE_COLOR_NORMAL, 
            ss->traffic.tx_pkts);
    __stat_traffic_get_string(worker_busy, CSP_TRAFFIC_LEN, SPATE_COLOR_NORMAL, 
            ss->traffic.tx_busy_pkts);

    stat_print("worker%2u      | %s|%s|%s|\n", worker_id, worker_rx, worker_tx, worker_busy);
}

static void _server_stat_print_workers()
{
    uint16_t                    i, nr;
    const server_stat_info_t    *w_info;

    nr = g_server_worker->ops->get_worker_nr();

    for (i=0; i<nr; ++i) {
        w_info = g_server_worker->ops->get_server_stat_info(i);

        _server_stat_print_worker(w_info, i);
    }

    stat_print("--------------+---------------+--------------+--------------|\n");
}



static void _server_stat_print_traffic_total_delta(server_stat_info_t *now, 
        server_stat_info_t *delta)
{
    char        total_rx    [CSP_TRAFFIC_LEN];
    char        total_tx    [CSP_TRAFFIC_LEN];
    char        total_busy  [CSP_TRAFFIC_LEN];
    char        delta_rx    [CSP_TRAFFIC_LEN];
    char        delta_tx    [CSP_TRAFFIC_LEN];
    char        delta_busy  [CSP_TRAFFIC_LEN];


    __stat_traffic_get_string(total_rx, CSP_TRAFFIC_LEN, SPATE_COLOR_GREEN, now->traffic.rx_pkts);
    __stat_traffic_get_string(total_tx, CSP_TRAFFIC_LEN, SPATE_COLOR_GREEN, now->traffic.tx_pkts);
    __stat_traffic_get_string(total_busy, CSP_TRAFFIC_LEN, SPATE_COLOR_NORMAL, 
            now->traffic.tx_busy_pkts);

    __stat_traffic_get_string(delta_rx, CSP_TRAFFIC_LEN, SPATE_COLOR_GREEN, delta->traffic.rx_pkts);
    __stat_traffic_get_string(delta_tx, CSP_TRAFFIC_LEN, SPATE_COLOR_GREEN, delta->traffic.tx_pkts);

    if (delta->traffic.tx_busy_pkts) {
        __stat_traffic_get_string(delta_busy, CSP_TRAFFIC_LEN, SPATE_COLOR_RED,
                delta->traffic.tx_busy_pkts);
    } else {
        __stat_traffic_get_string(delta_busy, CSP_TRAFFIC_LEN, SPATE_COLOR_NORMAL,
                delta->traffic.tx_busy_pkts);
    }
    

    stat_print("Total         | %s|%s|%s|\n", total_rx, total_tx, total_busy);

    stat_print("Delta         | %s|%s|%s|\n", delta_rx, delta_tx, delta_busy);

}


static inline void __server_stat_print_traffic_title(void)
{
    stat_print( "----------------------"
                "\033[1;37m Server  Traffic \033[0m"
                "----------------------\n");
    stat_print("              |            rx |           tx |      busy_tx |\n");
    stat_print("--------------+---------------+--------------+--------------|\n");
}

static inline void __server_stat_print_traffic_tail(void)
{
    stat_print("\n");
}

static inline void __server_stat_print_traffic_body(server_stat_t *ss)
{
    server_stat_info_t      delta;

    server_stat_info_delta(&delta, &ss->info_now, &ss->info_last);

    _server_stat_print_traffic_total_delta(&ss->info_now, &delta);
}

static inline void __server_stat_print_traffic(server_stat_t *ss)
{
    __server_stat_print_traffic_title();

    if (ss->base.cfg.worker_enable) {
        _server_stat_print_workers();
    }

    __server_stat_print_traffic_body(ss);

    __server_stat_print_traffic_tail();
}


void server_stat_print(server_stat_t *ss)
{
    __server_stat_print_traffic(ss);
}

