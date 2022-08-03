/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_OFFLOAD_SYSTEM_IMP_H__
#define __EBPF_OFFLOAD_SYSTEM_IMP_H__


#include "ebpf_offload_system.h"

#define EBPF_OFFLOAD_CMD_LENGTH     256

typedef struct {

    ebpf_offload_system_t       base;

    /*
     * private:
     */

    char                        cmd_attach[EBPF_OFFLOAD_CMD_LENGTH];
    char                        cmd_detach[EBPF_OFFLOAD_CMD_LENGTH];

} ebpf_offload_system_imp_t;



#endif /* __EBPF_OFFLOAD_SYSTEM_IMP_H__ */
