/*
 * Rodzhang
 *
 */

#ifndef __SPATE_DEBUG_H__
#define __SPATE_DEBUG_H__


#include <spate_core.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


static inline char *__ipv4_n_to_string(uint32_t ip)
{
    struct in_addr          in;

    in.s_addr = ip;

    return inet_ntoa(in);
}


static inline char *__ipv4_h_to_string(uint32_t ip)
{
    return __ipv4_n_to_string(htonl(ip));
}

static inline char *__mac_addr_to_string(uint8_t *mac, char *buf, uint32_t buf_len)
{
    snprintf(buf, buf_len, "%02x:%02x:%02x:%02x:%02x:%02x",
            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    buf[buf_len-1] = 0;

    return buf;
}


#endif /* __SPATE_DEBUG_H__ */
