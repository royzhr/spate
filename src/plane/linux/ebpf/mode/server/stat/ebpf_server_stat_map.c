/*
 *  Rodzhang
 *
 */

#include "ebpf_server_stat_map.h"


int  ebpf_server_stat_map_open(const char *mount_path)
{
    char                path[EBPF_MOUNT_PATH_MAX];
    int                 fd;

    sprintf(path, "%s/xdp/globals/spate_server_stat", mount_path);

    fd = bpf_obj_get(path);

    LOGW("ebpf config map: %s fd=%d", path, fd);

    return fd;
}

void ebpf_server_stat_map_close(int fd)
{
    close(fd);
}

void ebpf_server_stat_map_zero(int fd)
{
    int cpu_nr = libbpf_num_possible_cpus();
    server_stat_info_t          stats[cpu_nr]; 
    uint32_t                    key;

    memset(stats, 0, sizeof(server_stat_info_t)*cpu_nr);

    key = 0;

    bpf_map_update_elem(fd, &key, stats, BPF_ANY);
}

int  ebpf_server_stat_map_read(int fd, server_stat_info_t *st)
{
    int cpu_nr = libbpf_num_possible_cpus();
    server_stat_info_t          stats[cpu_nr]; 
    uint32_t                    key;
    int                         ret, i;
    
    memset(st, 0, sizeof(*st));

    key = 0;
    ret = bpf_map_lookup_elem(fd, &key, stats);
    if (ret < 0) {
        return ret;
    }

    for (i=0; i<cpu_nr; ++i) {
        __server_stat_info_increase(st, &stats[i]);
    }

    return 0;
}



