/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SERVER_STAT_API_H__
#define __EBPF_SERVER_STAT_API_H__


#include "../../ebpf_offload_component.h"
#include "../../../ebpf_offload_cfg.h"

ebpf_offload_component_t *ebpf_offload_component_server_stat_create(const ebpf_offload_cfg_t *cfg);


#endif /* __EBPF_SERVER_STAT_API_H__ */
