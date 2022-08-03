/*
 * Rodzhang
 */

#ifndef __FD_HELPER_H__
#define __FD_HELPER_H__


#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>


static inline int __set_noblocking(int fd)
{
    int                     flags;

    if (-1 == (flags = fcntl(fd, F_GETFL, 0))) {
        flags = 0;
    }

    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}


static inline int __set_blocking(int fd)
{
    int                     flags;

    if (-1 == (flags = fcntl(fd, F_GETFL, 0))) {
        flags = 0;
    }

    return fcntl(fd, F_SETFL, flags & (~O_NONBLOCK));
}



//extern pid_t            pxy_pid;
//#define FD_CLOSE(fd)    printf("###[%d]call close(%s-%d) fd=%d\n", pxy_pid, __FILE__, __LINE__, fd), close(fd)

#define FD_CLOSE(fd)    close(fd)



#endif /* __FD_HELPER_H__ */
