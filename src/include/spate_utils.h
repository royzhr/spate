/*
 * Rodzhang
 */

#ifndef __SPATE_UTILS_H__
#define __SPATE_UTILS_H__



#include <stddef.h>
#include <ctype.h>
#include <time.h>
#include <spate_core.h>


//#include "utils/list.h"
//#include "utils/jhash.h"
#include "utils/mem_barrier.h"
#include "utils/random32.h"
#include "utils/fd_helper.h"


#define spate_abs(val)    (( (val)>=0 ) ? (val) : -(val))

//对齐
#define alignment(s, a)     ( (s+(a-1)) & (~(a-1)) )


#define min_of(a, b) ( (a) > (b) ? (b) : (a) )


#define range_of(x, min, max)                                   \
    do {                                                        \
        if (x < min) {x = min;} else if (x > max) {x = max;}    \
    } while (0)

//判断 n 是否是 2 的幂 (包括2的0次幂)
#define is_power_of_2(n)    ( (n>0) && ( ((n) & (n-1)) == 0 ) )



#ifndef likely
#define likely(x)	__builtin_expect(!!(x), 1)
#endif /* likely */

#ifndef unlikely
#define unlikely(x)	__builtin_expect(!!(x), 0)
#endif /* unlikely */

#ifndef container_of
#define container_of(ptr, type, member) ({                      \
        typeof( ((type *)0)->member ) *__mptr = (ptr);    \
	        (type *)( (char *)__mptr - offsetof(type,member) );})
#endif


static inline char *__string_to_lower(char *s)
{
    char                *r;

    r = s;

    for (; *s!='\0'; s++) {
        *s = tolower(*s);
    }

    return r;
}


static inline int __spate_msleep(uint32_t ms)
{
    struct timespec     ts;
    int                 ret;

    ts.tv_sec  = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;

    ret = nanosleep(&ts, NULL);

    if (ret < 0) {
        LOGE("__spate_msleep faild: ms %u, errno: %d", ms, errno);
    }

    return ret;
}

static inline int __strcmp_prex(const char *in, const char *pattern)
{
    return strncmp(in, pattern, strlen(pattern));
}


#endif /* __SPATE_UTILS_H__ */
