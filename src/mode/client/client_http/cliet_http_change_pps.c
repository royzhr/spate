/*
 *  Rodzhang
 *
 */

#include "cliet_http_change_pps.h"
#include <spate_http.h>
#include <spate_config.h>
#include <spate_packet.h>


int client_http_change_pps(const char *uri, char *buf, int size, int *len)
{
    char                        val[SPATE_URI_PARAMS_SIZE];
    int                         ret;
    int                         u;
    uint32_t                    pps;

    ret = http_parse_uri_params(uri, "pps", val, sizeof(val));
    if (ret < 0) {
        return -1;
    }

    pps = __config_parse_uint32(val);

    g_packet->ops->change_pps_per_worker(pps);

    u = 0;
    u += sprintf(buf+u, "{\r\n");
    u += sprintf(buf+u, "\t\"Error\": 0,\r\n");
    u += sprintf(buf+u, "\t\"pps\": %d\r\n", pps);
    u += sprintf(buf+u, "}\r\n");

    *len = u;

    return 1;
}


