/*
 * Rodzhang
 *
 */

#include "log.h"
#include <spate_main.h>


#define __MAX_LOG_LINE  (2048)



void LOG_OUT(const char * _file_, int _line_, uint16_t level, 
        const char *format, va_list ap)
{
    char        _str[__MAX_LOG_LINE];
    int         _offset;
    size_t      n;
    FILE        *f;

    if (!__log_level_is_satisfy(level)) {                                                           
        return;
    }

    _offset = 0;
    n = __MAX_LOG_LINE-1;

    _offset += snprintf(_str+_offset, n-_offset, "%s(%d) [%s]: ",
            _file_, _line_, __log_level_tag(level));
    _offset += snprintf(_str+_offset, n-_offset, "%s", __log_level_color(level));
    _offset += vsnprintf(_str+_offset, n-_offset, format, ap);
    _offset += snprintf(_str+_offset, n-_offset, __COLOR_END);
    _offset += snprintf(_str+_offset, n-_offset, "\n");

    
    if (g_io) {
        f = g_io->ops->get_log();
        fprintf(f, "%s", _str);
        fflush(f);
    } else {
        printf("%s", _str);                                                                           
    }

}

