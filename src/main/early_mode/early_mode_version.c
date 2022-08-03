/*
 * Rodzhang
 *
 */

#include "early_mode_version.h"
#include <spate_print.h>


static const char *c_spate_version = "1.0.0";

const char *spate_version_get(void)
{
    return c_spate_version;
}

const char *__early_get_build_mode(char *buf, uint16_t buf_len)
{
#ifdef SPATE_DEBUG
    return __spate_color_string(buf, buf_len, SPATE_COLOR_RED, "(Debug)");
#else
    return __spate_color_string(buf, buf_len, SPATE_COLOR_GREEN, "(Release)");
#endif
}

const char *early_get_version(char *buf)
{
    char            str_build[128];

    sprintf(buf, "%s %s", c_spate_version, 
            __early_get_build_mode(str_build, sizeof(str_build)));

    return buf;
}

void early_mode_version(void)
{
    char    version[128];

    __spate_print("\n");
    __spate_print(" * Version   : %s\n", early_get_version(version));
    __spate_print(" * Author    : Rodzhang \n");
    __spate_print(" * Supporter : YuhuiWang \n");

    __spate_print("\n\n");
}


