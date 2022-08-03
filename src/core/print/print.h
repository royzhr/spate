/*
 * Rodzhang
 *
 */

#ifndef __PRINT_H__
#define __PRINT_H__


#include "print_color.h"

#define SPATE_PRINT_MAX_IN_LINE     1024


void spate_vprint(FILE *out, const char *format, va_list ap);
void spate_vprint_color(FILE * out, print_color_e color, const char *format, va_list ap);


/*
 * Param:
 * @buf      : [Ouput]   | the buf of color string
 * @buf_len  : [Input]   | the buf length
 * @color    : [Input]   | the color u want
 * @str      : [Input]   | the string u want set color
 *
 * Retrun Val: the color format string
 */
static inline const char *__spate_color_string(char *buf, uint16_t buf_len, 
        print_color_e color, const char *str)
{
    uint16_t    begin_len, str_len, end_len;

    begin_len = strlen(__get_print_color_begin(color));
    str_len   = strlen(str);
    end_len   = strlen(__get_print_color_end());
    
    if (begin_len+str_len+end_len+1 > buf_len) {
        return str;
    }

    strcpy(buf, __get_print_color_begin(color));
    strcpy(buf+begin_len, str);
    strcpy(buf+begin_len+str_len, __get_print_color_end());

    return buf;
}

static inline void __spate_print_color(print_color_e color, const char *format, ...)
{
    va_list     ap;

    va_start(ap, format);

    spate_vprint_color(stdout, color, format, ap);

    va_end(ap);
}

static inline void __spate_print(const char *format, ...)
{
    va_list     ap;

    va_start(ap, format);

    spate_vprint(stdout, format, ap);

    va_end(ap);
}




#endif /* __PRINT_H__ */
