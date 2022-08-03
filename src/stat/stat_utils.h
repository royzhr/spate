/*
 * Rodzhang
 *
 */

#ifndef __STAT_UTILS_H__
#define __STAT_UTILS_H__

#include "stat.h"
#include "stat_print.h"


#define CSP_TRAFFIC_LEN     64

static inline void __stat_traffic_get_string(char *buf, uint16_t buf_len,
        print_color_e color, uint64_t v)
{
    char        v_str[CSP_TRAFFIC_LEN];

    sprintf(v_str, "%13lu ", v);

    stat_color_string(buf, buf_len, color, v_str);

    //strcat(buf, "|");
}


void stat_cmd_build_error(stat_cmd_t *cmd, int error);


#endif /* __STAT_UTILS_H__ */
