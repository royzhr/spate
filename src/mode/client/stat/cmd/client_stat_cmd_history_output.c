/*
 *  Rodzhang
 *
 */

#include "client_stat_cmd_history_output.h"
#include "../client_stat_info_utils.h"



int client_stat_cmd_history_output(stat_cmd_t *cmd, const client_stat_info_t *ci, 
        int begin, int end)
{
    char                        *buf;
    int                         len;
    const client_stat_info_traffic_t*traffic;
    double                      mean, standard_deviation;;
    client_stat_latency_tp_t    tp;

    traffic = &ci->traffic;
    
    mean = client_stat_info_latency_mean(ci);
    standard_deviation = client_stat_info_latency_standard_deviation(ci);
    client_stat_info_latency_tp(ci, &tp);

    len = 0;
    buf = cmd->buf;

    len += sprintf(buf+len, "{\r\n");
    len += sprintf(buf+len, "\t\"Error\": 0,\r\n");
    len += sprintf(buf+len, "\t\"Begin\": %d,\r\n", begin);
    len += sprintf(buf+len, "\t\"End\": %d,\r\n", end);

    
    len += sprintf(buf+len, "\t\"Traffic\": {\r\n");
    len += sprintf(buf+len, "\t\t\"rx\": %lu,\r\n", traffic->rx_pkts);
    len += sprintf(buf+len, "\t\t\"tx\": %lu,\r\n", traffic->tx_pkts);
    len += sprintf(buf+len, "\t\t\"rtt_mean\": %.3f,\r\n", mean);
    len += sprintf(buf+len, "\t\t\"rtt_standard_deviation\": %.6f,\r\n", standard_deviation);
    len += sprintf(buf+len, "\t\t\"tp_50\": %.3f,\r\n", tp.tps[0]);
    len += sprintf(buf+len, "\t\t\"tp_90\": %.3f,\r\n", tp.tps[1]);
    len += sprintf(buf+len, "\t\t\"tp_95\": %.3f,\r\n", tp.tps[2]);
    len += sprintf(buf+len, "\t\t\"tp_99\": %.3f,\r\n", tp.tps[3]);
    len += sprintf(buf+len, "\t\t\"tx_busy\": %lu,\r\n", traffic->tx_busy_pkts);
    len += sprintf(buf+len, "\t\t\"rx_bugs\": %lu\r\n", traffic->bug_pkts);


    len += sprintf(buf+len, "\t}\r\n");

    len += sprintf(buf+len, "}\r\n");

    cmd->buf_len = len;

    return 1;
}

