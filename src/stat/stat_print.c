/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_main.h>
#include "stat_print.h"


const char *stat_color_string(char *buf, uint16_t buf_len, 
        print_color_e color, const char *str)
{
    return __spate_color_string(buf, buf_len, color, str);
}


void stat_print_color(print_color_e color, const char *format, ...)
{
    FILE        *out;
    va_list     ap;

    va_start(ap, format);

    out = g_io->ops->get_stdout();
    spate_vprint_color(out, color, format, ap);

    va_end(ap);
}


void stat_print(const char *format, ...)
{
    FILE        *out;
    va_list     ap;

    va_start(ap, format);

    out = g_io->ops->get_stdout();

    spate_vprint(out, format, ap);

    va_end(ap);
}


