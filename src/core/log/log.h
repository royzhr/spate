/*
 * Rodzhang
 *
 */

#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#include "log_level.h"





extern void LOG_OUT(const char * _file_, int _line_, uint16_t level, 
        const char *format, va_list ap);


static inline void __LOGD(const char *_file_, int _line_, const char *format, ...)
{
    va_list     ap;

    va_start(ap, format);

    LOG_OUT(_file_, _line_, SPT_LOG_DEBUG, format, ap);

    va_end(ap);
}

static inline void __LOGI(const char *_file_, int _line_, const char *format, ...)
{
    va_list     ap;

    va_start(ap, format);

    LOG_OUT(_file_, _line_, SPT_LOG_INFO, format, ap);

    va_end(ap);
}

static inline void __LOGW(const char *_file_, int _line_, const char *format, ...)
{
    va_list     ap;

    va_start(ap, format);

    LOG_OUT(_file_, _line_, SPT_LOG_WARN, format, ap);

    va_end(ap);
}

static inline void __LOGE(const char *_file_, int _line_, const char *format, ...)
{
    va_list     ap;

    va_start(ap, format);

    LOG_OUT(_file_, _line_, SPT_LOG_ERR, format, ap);

    va_end(ap);
}

#define LOGD(format, ...)   __LOGD(__FILE__, __LINE__, format, ## __VA_ARGS__)
#define LOGI(format, ...)   __LOGI(__FILE__, __LINE__, format, ## __VA_ARGS__)
#define LOGW(format, ...)   __LOGW(__FILE__, __LINE__, format, ## __VA_ARGS__)
#define LOGE(format, ...)   __LOGE(__FILE__, __LINE__, format, ## __VA_ARGS__)



#endif /* __LOG_H__ */
