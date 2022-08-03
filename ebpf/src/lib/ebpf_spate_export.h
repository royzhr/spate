/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_EXPORT_H__
#define __EBPF_SPATE_EXPORT_H__


#include <stdint.h>

#define __ntohl __builtin_bswap32
#define __htonl __builtin_bswap32
#define __htons __builtin_bswap16
#define __ntohs __builtin_bswap16

#ifndef likely
#define likely(x)	__builtin_expect(!!(x), 1)
#endif /* likely */

#ifndef unlikely
#define unlikely(x)	__builtin_expect(!!(x), 0)
#endif /* unlikely */

#include "../../../src/export/spate_export_ebpf.h"


#endif /* __EBPF_SPATE_EXPORT_H__ */

