/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SERVER_STAT_MAP_H__
#define __EBPF_SERVER_STAT_MAP_H__


#include "ebpf_server_stat.h"


int  ebpf_server_stat_map_open(const char *mount_path);
void ebpf_server_stat_map_close(int fd);
void ebpf_server_stat_map_zero(int fd);
int  ebpf_server_stat_map_read(int fd, server_stat_info_t *st);


#endif /* __EBPF_SERVER_STAT_MAP_H__ */
