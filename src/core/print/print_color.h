/*
 * Rodzhang
 *
 */

#ifndef __PRINT_COLOR_H__
#define __PRINT_COLOR_H__

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> 

typedef enum {
    SPATE_COLOR_NORMAL,
    SPATE_COLOR_RED,
    SPATE_COLOR_GREEN,
    SPATE_COLOR_YELLOW,
    SPATE_COLOR_BLUE,
    SPATE_COLOR_PURPLE,
    SPATE_COLOR_CYAN,

    SPATE_COLOR_B_NORMAL,
    SPATE_COLOR_B_RED,
    SPATE_COLOR_B_GREEN,
    SPATE_COLOR_B_YELLOW,
    SPATE_COLOR_B_BLUE,
    SPATE_COLOR_B_PURPLE,
    SPATE_COLOR_B_CYAN,
} print_color_e;


static inline const char *__get_print_color_begin(print_color_e color)
{
    switch(color) {
        case SPATE_COLOR_RED:
            return "\033[0;31m";
            break;

        case SPATE_COLOR_GREEN:
            return "\033[0;32m";
            break;

        case SPATE_COLOR_YELLOW:
            return "\033[0;33m";
            break;

        case SPATE_COLOR_BLUE:
            return "\033[0;34m";
            break;

        case SPATE_COLOR_PURPLE:
            return "\033[0;35m";
            break;

        case SPATE_COLOR_CYAN:
            return "\033[0;36m";
            break;

        case SPATE_COLOR_B_NORMAL:
            return "\033[1;37m";
            break;

        case SPATE_COLOR_B_RED:
            return "\033[1;31m";
            break;

        case SPATE_COLOR_B_GREEN:
            return "\033[1;32m";
            break;

        case SPATE_COLOR_B_YELLOW:
            return "\033[1;33m";
            break;

        case SPATE_COLOR_B_BLUE:
            return "\033[1;34m";
            break;

        case SPATE_COLOR_B_PURPLE:
            return "\033[1;35m";
            break;

        case SPATE_COLOR_B_CYAN:
            return "\033[1;36m";
            break;

        default:
            break;
    }

    return "\033[0;37m";
}

static inline const char *__get_print_color_end(void)
{
    return "\033[0m";
}





#endif /* __PRINT_COLOR_H__ */
