/*
 *  Rodzhang
 *
 */

#include "ebpf_client_stat_map.h"


int  ebpf_client_stat_map_open(const char *mount_path)
{
    char                path[EBPF_MOUNT_PATH_MAX*2];
    int                 fd;

    snprintf(path, sizeof(path)-1, 
            "%s/xdp/globals/spate_client_stat", mount_path);

    fd = bpf_obj_get(path);

    LOGW("ebpf config map: %s fd=%d", path, fd);

    return fd;
}

void ebpf_client_stat_map_close(int fd)
{
    close(fd);
}

void ebpf_client_stat_map_zero(int fd)
{
    int cpu_nr = libbpf_num_possible_cpus();
    spate_ebpf_client_stat_t    stats[cpu_nr]; 
    uint32_t                    key;

    memset(stats, 0, sizeof(spate_ebpf_client_stat_t)*cpu_nr);

    key = 0;

    bpf_map_update_elem(fd, &key, stats, BPF_ANY);
}

int  ebpf_client_stat_map_read(int fd, spate_ebpf_client_stat_t *st)
{
    int cpu_nr = libbpf_num_possible_cpus();
    spate_ebpf_client_stat_t    stats[cpu_nr]; 
    uint32_t                    key;
    int                         ret, i;
    
    memset(st, 0, sizeof(*st));

    key = 0;
    ret = bpf_map_lookup_elem(fd, &key, stats);
    if (ret < 0) {
        return ret;
    }

    for (i=0; i<cpu_nr; ++i) {
        __client_stat_info_increase_traffic(&st->traffic, &stats[i].traffic);
        __client_stat_info_increase_latency(&st->latency, &stats[i].latency);
    }

    return 0;
}


