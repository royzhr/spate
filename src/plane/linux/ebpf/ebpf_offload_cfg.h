/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_OFFLOAD_CFG_H__
#define __EBPF_OFFLOAD_CFG_H__



#include <spate_core.h>

#define EBPF_MOUNT_PATH_MAX   256

typedef struct {

    int                 offload_enable;

    const char          *obj_path;


    char                mount_path[EBPF_MOUNT_PATH_MAX];

} ebpf_offload_cfg_t;



#endif /* __EBPF_OFFLOAD_CFG_H__ */

