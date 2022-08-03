/*
 *  Rodzhang
 *
 */

#include "stat_utils.h"



void stat_cmd_build_error(stat_cmd_t *cmd, int error)
{
    char                        *buf;
    int                         len;

    len = 0;
    buf = cmd->buf;

    len += sprintf(buf+len, "{\r\n");
    len += sprintf(buf+len, "\t\"Error\": %d\r\n", error);
    len += sprintf(buf+len, "}\r\n");

    cmd->buf_len = len;
}

