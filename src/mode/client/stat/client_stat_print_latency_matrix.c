/*
 * Rodzhang
 *
 */

#include "client_stat_print_latency_matrix.h"


static inline void __print_matrix_element(uint64_t cnt, print_color_e color)
{
    if (cnt == 0) {
        stat_print("        ");
    } else {
        stat_print_color(color, "%7lu ", cnt);
    }
}

static inline void __print_matrix_row(client_stat_info_latency_t *latency, 
        uint16_t begin, print_color_e color)
{
    uint16_t                i;
    uint64_t                cnt;

    for (i=0; i<10; ++i) {
        
        cnt = latency->cnt_tbl[begin+i];

        __print_matrix_element(cnt, color);
    }
}


void client_stat_print_latency_matrix(client_stat_info_latency_t *latency, const char *title)
{
    uint16_t                i;

    stat_print( "--------------------------------"
                "\033[1;37m Latency Distribution of  %s \033[0m"
                "--------------------------------\n", title);

    stat_print("  range(ms)   | ");

    for (i=0; i<10; ++i) {
        stat_print("%d     ~ ", i);
    };
    stat_print("  \n");


    stat_print(" 0.01 -  0.1  | ");
    __print_matrix_row(latency, 0, SPATE_COLOR_GREEN);
    stat_print("  \n");

    stat_print("  0.1 -    1  | ");
    __print_matrix_row(latency, 10, SPATE_COLOR_NORMAL);
    stat_print("  \n");

    stat_print("    1 -   10  | ");
    __print_matrix_row(latency, 20, SPATE_COLOR_NORMAL);
    stat_print("  \n");

    stat_print("   10 -  100  | ");
    __print_matrix_row(latency, 30, SPATE_COLOR_YELLOW);
    stat_print("  \n");

    stat_print("  100 - 1000  | ");
    __print_matrix_row(latency, 40, SPATE_COLOR_RED);
    stat_print("  \n");

    stat_print(" 1000 -10000  | ");
    __print_matrix_row(latency, 50, SPATE_COLOR_B_RED);
    stat_print("  \n");

    stat_print("10000 -  INF  | ");
    __print_matrix_element(latency->cnt_tbl[60], SPATE_COLOR_B_RED);
    stat_print("  \n");
}

