/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_CLIENT_STAT_MAP_H__
#define __EBPF_CLIENT_STAT_MAP_H__


#include "ebpf_client_stat.h"


int  ebpf_client_stat_map_open(const char *mount_path);
void ebpf_client_stat_map_close(int fd);
void ebpf_client_stat_map_zero(int fd);
int  ebpf_client_stat_map_read(int fd, spate_ebpf_client_stat_t *st);

#endif /* __EBPF_CLIENT_STAT_MAP_H__ */
