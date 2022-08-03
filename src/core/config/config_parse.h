/*
 * Rodzhang
 *
 */

#ifndef __CONFIG_PARSE_H__
#define __CONFIG_PARSE_H__


#include <spate_core.h>
#include <ctype.h>


/*
 * Strip extra spaces before and after the string
 */
static inline char *__config_string_strip_space(char *str)
{
    char        *ret, *t;

    ret = str;

    while (*ret) {
        if (isspace(*ret)) {
            ++ret;
        } else {
            break;
        }
    }

    t = ret + strlen(ret) - 1;

    while (t>=ret) {
        if (isspace(*t) || *t=='\r' || *t=='\n') {
            *t = 0;
        } else {
            break;
        }
        --t;
    }

    return ret;
}


static inline uint16_t __config_parse_uint16(const char *str)
{
    return atoi(str);
}

static inline uint32_t __config_parse_uint32(const char *str)
{
    return atoi(str);
}

static inline int __config_parse_bool(const char *str)
{
    return atoi(str) ? 1 : 0;
}

/*
 * Parse to host byte order of ipv4
 */
static inline int __config_parse_ipv4(uint32_t *ip, const char *str)
{
    uint32_t                v;
    uint8_t                 b[4];
    int                     i;

    i = 0;
    do {

        v = atoi(str);
        if (v > 255) {
            return -1;
        }
        b[i++] = (uint8_t)v;

        str = strchr(str, '.');
        if (str) {
            str = str+1;
        } else {
            break;
        }

    } while(i<4);
    
    if (i == 4) {
        memcpy(ip, b, 4);

        *ip = ntohl(*ip);

        return 0;
    }

    return -1;
}


static inline uint8_t __config_char_to_hex(char ch)
{
    if (ch >= '0' && ch <='9') {
        return ch - '0';
    } else if (ch >= 'a' && ch <= 'f') {
        return ch - 'a' + 10;
    } else if (ch >= 'A' && ch <='F') {
        return ch - 'A' + 10;
    }

    return 0;
}

static inline uint8_t __config_parse_hex_byte(const char *str)
{
    uint8_t                 b1, b2;

    b1 = __config_char_to_hex(str[0]);
    b2 = __config_char_to_hex(str[1]);

    return (b1<<4) | b2;
}

static inline int __config_parse_mac_addr(uint8_t mac_addr[6], const char *str)
{
    int                     i;

    i = 0;

    do {
        mac_addr[i++] = __config_parse_hex_byte(str);

        str = strchr(str, ':');
        if (str) {
            str = str+1;
        } else {
            break;
        }
    } while (i<6) ;

    if (i == 6) {
        return 0;
    }

    return -1;
}




#endif /* __CONFIG_PARSE_H__ */
