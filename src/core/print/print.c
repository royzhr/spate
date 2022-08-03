/*
 * Rodzhang
 *
 */

#include "print.h"

void spate_vprint(FILE *out, const char *format, va_list ap)
{
    vfprintf(out, format, ap);
}

void spate_vprint_color(FILE * out, print_color_e color, const char *format, va_list ap)
{
    if (color == SPATE_COLOR_NORMAL) {
        vfprintf(out, format, ap);
    } else {
        char        buf[SPATE_PRINT_MAX_IN_LINE];

        vfprintf(out, __spate_color_string(buf, sizeof(buf), color, format), ap);
    }
}

