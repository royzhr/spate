/*
 * Rodzhang
 *
 */

#include "drop_reason.h"





#if 0
static void _drop_tcp(struct tcp_hdr *tcp)
{
    char            str[256];
    uint8_t         *datas;
    int             i, off;

    datas = (uint8_t)(tcp);

    off = 0;
    off = sprintf(str, "tcphdr flags=0x%x mem:\n", (uint32_t)(tcp->tcp_flags&0x00FF));
    for (i=0; i<20; ++i) {

        off = sprintf(str+off, "%02x ", datas[i]);
    }

    LOGD(str);
}
#endif


void spate_drop_with_reason(spate_drop_reason_e reason, __UNUSED__ void *arg)
{
    LOGD("spate drop with reason: %d", reason);

    /*
    switch (reason) {
        case DROP_TCPHDR_ERROR:
        case DROP_TCP_NOACK:
            _drop_tcp((struct tcp_hdr *)arg);
            break;

        default:
            break;
    }
    */

}


