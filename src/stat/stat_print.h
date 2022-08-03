/*
 * Rodzhang
 *
 */

#ifndef __STAT_PRINT_H__
#define __STAT_PRINT_H__


#include <spate_print.h>



void stat_print_color(print_color_e color, const char *format, ...);

void stat_print(const char *format, ...);

const char *stat_color_string(char *buf, uint16_t buf_len, 
        print_color_e color, const char *str);



#endif /* __STAT_PRINT_H__ */
