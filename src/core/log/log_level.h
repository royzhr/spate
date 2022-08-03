/*
 * Rodzhang
 *
 */

#ifndef __LOG_LEVEL_H__
#define __LOG_LEVEL_H__


#include <stdio.h>
#include <stdlib.h>

/*
 * Log Level Define
 */
#define SPT_LOG_STAT    7
#define SPT_LOG_ERR     6
#define SPT_LOG_WARN    5
#define SPT_LOG_INFO    4
#define SPT_LOG_DEBUG   3


#define __COLOR_WARNING "\033[33m"
#define __COLOR_INFO    "\033[32m"
#define __COLOR_ERROR   "\033[47;31m"
#define __COLOR_END     "\033[0m"


static inline const char * __log_level_color(uint16_t log_level)
{
    switch (log_level) {
        case SPT_LOG_ERR:
            return __COLOR_ERROR;
        case SPT_LOG_WARN:
            return __COLOR_WARNING;
        case SPT_LOG_INFO:
            return __COLOR_INFO;
        default:
            return "";
    }
}

static inline const char * __log_level_tag(uint16_t log_level)
{
    switch (log_level) {
        case SPT_LOG_ERR:
            return "E";
        case SPT_LOG_WARN:
            return "W";
        case SPT_LOG_INFO:
            return "I";
        case SPT_LOG_DEBUG:
            return "D";
        default:
            return "";
    }
}

/*
 * Log's output level setting
 */
static inline uint16_t __log_level_config(void)
{
    return 0;
}

/*
 * Check Log level is satisfy
 */
static inline int __log_level_is_satisfy(uint16_t level)
{
    if (level < __log_level_config()) {
        return 0;
    }
    
    return 1;
}




#endif /* __LOG_LEVEL_H__ */
