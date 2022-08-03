/*
 * Rodzhang
 *
 */

#ifndef __LINUX_FILTER_MODE_H__
#define __LINUX_FILTER_MODE_H__


#include <stdint.h>

int build_filter_string_mode_client(char *str, uint16_t len);
int build_filter_string_mode_server(char *str, uint16_t len);


#define FILTER_STRING_PRE(is_first, p)      \
    if (is_first) {                         \
        is_first = 0;                       \
    } else {                                \
        p += sprintf(p, "or ");                \
    } 




#endif /* __LINUX_FILTER_MODE_H__ */
