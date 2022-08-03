/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SERVER_H__
#define __EBPF_SERVER_H__



#include "../ebpf_offload_mode.h"


ebpf_offload_mode_t *ebpf_offload_mode_server_create(const ebpf_offload_cfg_t *cfg);


#endif /* __EBPF_SERVER_H__ */
