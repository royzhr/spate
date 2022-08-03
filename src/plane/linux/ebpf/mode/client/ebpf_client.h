/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_CLIENT_H__
#define __EBPF_CLIENT_H__


#include "../ebpf_offload_mode.h"


ebpf_offload_mode_t *ebpf_offload_mode_client_create(const ebpf_offload_cfg_t *cfg);


#endif /* __EBPF_CLIENT_H__ */
