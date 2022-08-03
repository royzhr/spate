/*
 * Rodzhang
 *
 */

#ifndef __SPATE_DEFINE_H__
#define __SPATE_DEFINE_H__


#include <stdint.h>
#include <arpa/inet.h>


#define __UNUSED__   __attribute__((unused))



//the max char in one line of config file
#define CFG_MAX_PER_LINE    (1023)

#define SPATE_MAX_PATH      (256)


typedef enum {
    SPATE_UNKNOW = 0,

    SPATE_UDP = 0x1,
    SPATE_TCP = 0x2,

} spate_proto_e;

static inline uint8_t __spate_proto_to_ip_proto(spate_proto_e sp)
{
    if (sp == SPATE_UDP) {
        return IPPROTO_UDP;
    } else {
        return IPPROTO_TCP;
    }
}


#define SPATE_MAX_BURST             1024




typedef enum {
    SPATE_MODE_CLIENT = 0,
    SPATE_MODE_SERVER,
    SPATE_MODE_HELP,
    SPATE_MODE_VERSION,
    SPATE_MODE_SHOW,
    SPATE_MODE_LOG,
} spate_mode_e;



#define SPATE_MAX_WORKER       (128)

#include "../export/ebpf_define.h"


#endif /* __SPATE_DEFINE_H__ */
