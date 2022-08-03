/*
 * Rodzhang
 *
 */

#include "client_stat_print.h"
#include "client_stat_print_traffic.h"
#include "../worker/client_worker.h"



static inline void __latency_to_string(char *buf, uint16_t buf_len, uint32_t us)
{
    float               ms;
    print_color_e       color;
    char                ms_str[CSP_TRAFFIC_LEN];

    if (us == 0) {
        sprintf(buf, "           ");
        return;
    }

    if (us > 100000) {          //100ms
       color = SPATE_COLOR_B_RED; 
    } else if (us > 10000) {    //10ms
        color = SPATE_COLOR_YELLOW;
    } else if (us > 1000) {     //1ms
        color = SPATE_COLOR_NORMAL;
    } else {
        color = SPATE_COLOR_GREEN;
    }

    ms = (us / 1000.0f);

    sprintf(ms_str, " %10.2f", ms);
    
    stat_color_string(buf, buf_len, color, ms_str);
}

static void _client_stat_get_avg_latency_string(char *buf, uint16_t buf_len, client_stat_info_t *cs)
{
    uint32_t        us;

    if (cs->traffic.rx_pkts) {
        us = cs->latency.total_us / cs->traffic.rx_pkts;
    } else {
        us = 0;
    }

    __latency_to_string(buf, buf_len, us);
}



static void _client_stat_print_worker(const client_stat_info_t *cs, uint16_t worker_id)
{
    char        worker_rx    [CSP_TRAFFIC_LEN];
    char        worker_tx    [CSP_TRAFFIC_LEN];
    char        worker_busy  [CSP_TRAFFIC_LEN];

    __stat_traffic_get_string(worker_rx, CSP_TRAFFIC_LEN, SPATE_COLOR_NORMAL, 
            cs->traffic.rx_pkts);
    __stat_traffic_get_string(worker_tx, CSP_TRAFFIC_LEN, SPATE_COLOR_NORMAL, 
            cs->traffic.tx_pkts);
    __stat_traffic_get_string(worker_busy, CSP_TRAFFIC_LEN, SPATE_COLOR_NORMAL, 
            cs->traffic.tx_busy_pkts);

    stat_print("worker%2u      | %s|%s|%s|                  |               |\n", 
            worker_id, worker_rx, worker_tx, worker_busy);
}

static void _client_stat_print_workers()
{
    uint16_t                    i, nr;
    const client_stat_info_t    *w_info;

    nr = g_client_worker->ops->get_worker_nr();

    for (i=0; i<nr; ++i) {

        w_info = g_client_worker->ops->get_client_stat_info(i);

        _client_stat_print_worker(w_info, i);
    }
    stat_print("--------------+---------------+--------------+--------------+"
            "------------------+---------------|\n");
}


static inline void __client_stat_print_traffic_title(void)
{
    stat_print( "---------------------------------------"
                "\033[1;37m  Client Traffic  \033[0m"
                "---------------------------------------\n");

    stat_print("              |            rx |           tx |      busy_tx |  avg-latency(ms) |"
            "  may bug pkts |\n");
    stat_print("--------------+---------------+--------------+--------------+"
            "------------------+---------------|\n");
}



static void _client_stat_print_traffic_body(client_stat_info_t *now, client_stat_info_t *delta)
{
    char        total_rx    [CSP_TRAFFIC_LEN];
    char        total_tx    [CSP_TRAFFIC_LEN];
    char        total_busy  [CSP_TRAFFIC_LEN];
    char        total_avg   [CSP_TRAFFIC_LEN];
    char        total_bug   [CSP_TRAFFIC_LEN];
    char        delta_rx    [CSP_TRAFFIC_LEN];
    char        delta_tx    [CSP_TRAFFIC_LEN];
    char        delta_busy  [CSP_TRAFFIC_LEN];
    char        delta_avg   [CSP_TRAFFIC_LEN];
    char        delta_bug   [CSP_TRAFFIC_LEN];


    __stat_traffic_get_string(total_rx,   CSP_TRAFFIC_LEN, SPATE_COLOR_GREEN, 
            now->traffic.rx_pkts);
    __stat_traffic_get_string(total_tx,   CSP_TRAFFIC_LEN, SPATE_COLOR_GREEN, 
            now->traffic.tx_pkts);
    __stat_traffic_get_string(total_busy, CSP_TRAFFIC_LEN, SPATE_COLOR_NORMAL, 
            now->traffic.tx_busy_pkts);
    __stat_traffic_get_string(total_bug,  CSP_TRAFFIC_LEN, SPATE_COLOR_NORMAL, 
            now->traffic.bug_pkts);

    __stat_traffic_get_string(delta_rx,   CSP_TRAFFIC_LEN, SPATE_COLOR_GREEN, 
            delta->traffic.rx_pkts);
    __stat_traffic_get_string(delta_tx,   CSP_TRAFFIC_LEN, SPATE_COLOR_GREEN, 
            delta->traffic.tx_pkts);
    __stat_traffic_get_string(delta_bug,  CSP_TRAFFIC_LEN, SPATE_COLOR_NORMAL, 
            delta->traffic.bug_pkts);

    if (delta->traffic.tx_busy_pkts) {
        __stat_traffic_get_string(delta_busy, CSP_TRAFFIC_LEN, SPATE_COLOR_RED,
                delta->traffic.tx_busy_pkts);
    } else {
        __stat_traffic_get_string(delta_busy, CSP_TRAFFIC_LEN, SPATE_COLOR_NORMAL,
                delta->traffic.tx_busy_pkts);
    }

    _client_stat_get_avg_latency_string(total_avg, CSP_TRAFFIC_LEN, now);
    _client_stat_get_avg_latency_string(delta_avg, CSP_TRAFFIC_LEN, delta);
    

    stat_print("Total         | %s|%s|%s|   %s    | %s|\n", 
            total_rx, total_tx, total_busy, total_avg, total_bug);
    stat_print("Delta         | %s|%s|%s|   %s    | %s|\n", 
            delta_rx, delta_tx, delta_busy, delta_avg, delta_bug);
}

void client_stat_print_traffic(client_stat_t *cs, client_stat_info_t *delta)
{
    __client_stat_print_traffic_title();

    if (cs->base.cfg.worker_enable) {
        _client_stat_print_workers(); 
    }

    _client_stat_print_traffic_body(&cs->info_now, delta);

}
