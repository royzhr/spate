/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_SERVER_MAP_H__
#define __EBPF_SPATE_SERVER_MAP_H__


#include "ebpf_spate_server_dep.h"

struct bpf_elf_map spate_server_config SEC("maps") = {
    .type           = BPF_MAP_TYPE_ARRAY,
    .size_key       = sizeof(uint32_t),
    .size_value     = sizeof(spate_ebpf_server_config_t),
    .pinning        = PIN_GLOBAL_NS,
    .max_elem       = 1,
};

struct bpf_elf_map spate_server_stat SEC("maps") = {
    .type           = BPF_MAP_TYPE_PERCPU_ARRAY,
    .size_key       = sizeof(uint32_t),
    .size_value     = sizeof(server_stat_info_t),
    .pinning        = PIN_GLOBAL_NS,
    .max_elem       = 1,
};


#endif /* __EBPF_SPATE_SERVER_MAP_H__ */
