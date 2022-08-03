/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_CLIENT_MAP_H__
#define __EBPF_SPATE_CLIENT_MAP_H__



#include "ebpf_spate_client_dep.h"


struct bpf_elf_map spate_client_config SEC("maps") = {
    .type           = BPF_MAP_TYPE_ARRAY,
    .size_key       = sizeof(uint32_t),
    .size_value     = sizeof(spate_ebpf_client_config_t),
    .pinning        = PIN_GLOBAL_NS,
    .max_elem       = 1,
};

struct bpf_elf_map spate_client_stat SEC("maps") = {
    .type           = BPF_MAP_TYPE_PERCPU_ARRAY,
    .size_key       = sizeof(uint32_t),
    .size_value     = sizeof(spate_ebpf_client_stat_t),
    .pinning        = PIN_GLOBAL_NS,
    .max_elem       = 1,
};




#endif /* __EBPF_SPATE_CLIENT_MAP_H__ */
