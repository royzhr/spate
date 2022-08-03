/*
 * Rodzhang
 *
 */

#ifndef __DROP_REASON_H__
#define __DROP_REASON_H__


#include <spate_core.h>

typedef enum {
    DROP_NO_REASON = 0,
    DROP_ETHHDR_ERROR,
    DROP_ETH_DMAC_REJECT,
    DROP_ETH_PROTO_REJECT,

    DROP_ARP_REJECT,
    DROP_IPHDR_ERROR,
    DROP_IP_PROTO_REJECT,
    DROP_UDPHDR_ERROR,

    DROP_TCPHDR_ERROR,
    DROP_TCP_NOACK,

    DROP_PAYLOAD_SIZE_ERROR,
    DROP_PAYLOAD_TAGS_ERROR,
    DROP_PAYLOAD_CYCLES_ERROR,

} spate_drop_reason_e;


void spate_drop_with_reason(spate_drop_reason_e reason, void *arg);



//#define SPATE_DROP(reason, arg)    spate_drop_with_reason(reason, arg)
#define SPATE_DROP(reason, arg)




#endif /* __DROP_REASON_H__ */

